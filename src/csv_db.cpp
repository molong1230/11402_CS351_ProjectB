#include "csv_db.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

namespace csvdb {

namespace {

std::string trim(const std::string& text) {
    std::size_t left = 0;
    while (left < text.size() && std::isspace(static_cast<unsigned char>(text[left])) != 0) {
        ++left;
    }
    if (left == text.size()) {
        return "";
    }

    std::size_t right = text.size() - 1;
    while (right > left && std::isspace(static_cast<unsigned char>(text[right])) != 0) {
        --right;
    }
    return text.substr(left, right - left + 1);
}

std::string to_upper(const std::string& text) {
    std::string out = text;
    std::transform(out.begin(), out.end(), out.begin(), [](unsigned char ch) {
        return static_cast<char>(std::toupper(ch));
    });
    return out;
}

std::vector<std::string> split_csv_line(const std::string& line) {
    std::vector<std::string> fields;
    std::string current;
    bool in_quotes = false;

    for (std::size_t i = 0; i < line.size(); ++i) {
        const char c = line[i];
        if (c == '"') {
            if (in_quotes && i + 1 < line.size() && line[i + 1] == '"') {
                current.push_back('"');
                ++i;
            } else {
                in_quotes = !in_quotes;
            }
        } else if (c == ',' && !in_quotes) {
            fields.push_back(trim(current));
            current.clear();
        } else {
            current.push_back(c);
        }
    }

    fields.push_back(trim(current));
    return fields;
}

std::vector<std::string> split_list(const std::string& text) {
    std::vector<std::string> parts;
    std::string token;
    std::stringstream ss(text);
    while (std::getline(ss, token, ',')) {
        const std::string item = trim(token);
        if (!item.empty()) {
            parts.push_back(item);
        }
    }
    return parts;
}

int find_column_index(const std::unordered_map<std::string, std::size_t>& index_by_column, const std::string& name) {
    const auto it = index_by_column.find(name);
    if (it == index_by_column.end()) {
        return -1;
    }
    return static_cast<int>(it->second);
}

}  // namespace

void CsvTable::load_from_file(const std::string& path) {
    std::ifstream in(path);
    if (!in.is_open()) {
        throw std::runtime_error("Cannot open CSV file: " + path);
    }

    std::string line;
    if (!std::getline(in, line)) {
        throw std::runtime_error("CSV file is empty: " + path);
    }

    header_ = split_csv_line(line);
    if (header_.empty()) {
        throw std::runtime_error("CSV header is empty: " + path);
    }

    rows_.clear();
    while (std::getline(in, line)) {
        if (trim(line).empty()) {
            continue;
        }

        auto row = split_csv_line(line);
        if (row.size() != header_.size()) {
            throw std::runtime_error("CSV row has different column count: " + line);
        }
        rows_.push_back(std::move(row));
    }
}

const std::vector<std::string>& CsvTable::header() const {
    return header_;
}

const std::vector<std::vector<std::string>>& CsvTable::rows() const {
    return rows_;
}

Query QueryEngine::parse_query(const std::string& query_text) const {
    const std::string query = trim(query_text);
    const std::string upper = to_upper(query);

    if (upper.rfind("SELECT ", 0) != 0) {
        throw std::runtime_error("Query must start with SELECT");
    }

    Query parsed;

    const std::size_t where_pos = upper.find(" WHERE ");
    const std::size_t order_pos = upper.find(" ORDER BY ");
    const std::size_t limit_pos = upper.find(" LIMIT ");

    std::size_t end_of_select = query.size();
    if (where_pos != std::string::npos) {
        end_of_select = std::min(end_of_select, where_pos);
    }
    if (order_pos != std::string::npos) {
        end_of_select = std::min(end_of_select, order_pos);
    }
    if (limit_pos != std::string::npos) {
        end_of_select = std::min(end_of_select, limit_pos);
    }

    const std::string select_part = trim(query.substr(7, end_of_select - 7));
    if (to_upper(select_part) == "COUNT(*)") {
        parsed.count_star = true;
    } else if (select_part == "*") {
        parsed.select_columns.clear();
    } else {
        parsed.select_columns = split_list(select_part);
        if (parsed.select_columns.empty()) {
            throw std::runtime_error("SELECT list is empty");
        }
    }

    if (where_pos != std::string::npos) {
        std::size_t where_end = query.size();
        if (order_pos != std::string::npos && order_pos > where_pos) {
            where_end = std::min(where_end, order_pos);
        }
        if (limit_pos != std::string::npos && limit_pos > where_pos) {
            where_end = std::min(where_end, limit_pos);
        }

        const std::string where_body = trim(query.substr(where_pos + 7, where_end - (where_pos + 7)));
        const std::size_t eq_pos = where_body.find('=');
        if (eq_pos == std::string::npos) {
            throw std::runtime_error("WHERE must use equality, e.g. WHERE name=Alice");
        }

        parsed.where_column = trim(where_body.substr(0, eq_pos));
        parsed.where_value = trim(where_body.substr(eq_pos + 1));

        if (parsed.where_column->empty()) {
            throw std::runtime_error("WHERE column is empty");
        }
        if (parsed.where_value->empty()) {
            throw std::runtime_error("WHERE value is empty");
        }
    }

    if (order_pos != std::string::npos) {
        std::size_t order_end = query.size();
        if (limit_pos != std::string::npos && limit_pos > order_pos) {
            order_end = std::min(order_end, limit_pos);
        }

        std::string order_body = trim(query.substr(order_pos + 10, order_end - (order_pos + 10)));
        std::stringstream os(order_body);
        std::string column;
        std::string direction;
        os >> column;
        os >> direction;

        if (column.empty()) {
            throw std::runtime_error("ORDER BY column is empty");
        }

        parsed.order_by_column = column;
        if (!direction.empty()) {
            const std::string upper_dir = to_upper(direction);
            if (upper_dir == "DESC") {
                parsed.order_desc = true;
            } else if (upper_dir == "ASC") {
                parsed.order_desc = false;
            } else {
                throw std::runtime_error("ORDER BY direction must be ASC or DESC");
            }
        }
    }

    if (limit_pos != std::string::npos) {
        const std::string limit_body = trim(query.substr(limit_pos + 7));
        std::size_t offset = 0;
        const unsigned long value = std::stoul(limit_body, &offset);
        if (offset != limit_body.size()) {
            throw std::runtime_error("LIMIT must be an integer");
        }
        parsed.limit = static_cast<std::size_t>(value);
    }

    return parsed;
}

QueryResult QueryEngine::execute(const CsvTable& table, const Query& query) const {
    QueryResult result;
    std::unordered_map<std::string, std::size_t> index_by_column;
    for (std::size_t i = 0; i < table.header().size(); ++i) {
        index_by_column[table.header()[i]] = i;
    }

    int where_idx = -1;
    if (query.where_column.has_value()) {
        where_idx = find_column_index(index_by_column, query.where_column.value());
        if (where_idx < 0) {
            throw std::runtime_error("Unknown WHERE column: " + query.where_column.value());
        }
    }

    if (query.count_star) {
        std::size_t count = 0;
        for (const auto& row : table.rows()) {
            if (where_idx >= 0 && row[static_cast<std::size_t>(where_idx)] != query.where_value.value()) {
                continue;
            }
            ++count;
        }
        result.header = {"count"};
        result.rows = {{std::to_string(count)}};
        return result;
    }

    std::vector<std::size_t> selected_indices;
    if (query.select_columns.empty()) {
        for (std::size_t i = 0; i < table.header().size(); ++i) {
            selected_indices.push_back(i);
            result.header.push_back(table.header()[i]);
        }
    } else {
        for (const auto& col : query.select_columns) {
            const int idx = find_column_index(index_by_column, col);
            if (idx < 0) {
                throw std::runtime_error("Unknown SELECT column: " + col);
            }
            selected_indices.push_back(static_cast<std::size_t>(idx));
            result.header.push_back(col);
        }
    }

    std::vector<std::vector<std::string>> filtered_rows;
    for (const auto& row : table.rows()) {
        if (where_idx >= 0 && row[static_cast<std::size_t>(where_idx)] != query.where_value.value()) {
            continue;
        }
        filtered_rows.push_back(row);
    }

    if (query.order_by_column.has_value()) {
        const int order_idx = find_column_index(index_by_column, query.order_by_column.value());
        if (order_idx < 0) {
            throw std::runtime_error("Unknown ORDER BY column: " + query.order_by_column.value());
        }

        std::sort(filtered_rows.begin(), filtered_rows.end(), [&](const auto& lhs, const auto& rhs) {
            const auto& lv = lhs[static_cast<std::size_t>(order_idx)];
            const auto& rv = rhs[static_cast<std::size_t>(order_idx)];
            return query.order_desc ? lv > rv : lv < rv;
        });
    }

    for (const auto& row : filtered_rows) {
        std::vector<std::string> out_row;
        out_row.reserve(selected_indices.size());
        for (std::size_t idx : selected_indices) {
            out_row.push_back(row[idx]);
        }
        result.rows.push_back(std::move(out_row));
    }

    if (query.limit.has_value() && query.limit.value() < result.rows.size()) {
        result.rows.resize(query.limit.value());
    }

    return result;
}

}  // namespace csvdb

#ifndef CSV_DB_HPP
#define CSV_DB_HPP

#include <optional>
#include <string>
#include <vector>

namespace csvdb {

struct Query {
    std::vector<std::string> select_columns;
    bool count_star = false;

    std::optional<std::string> where_column;
    std::optional<std::string> where_value;

    std::optional<std::string> order_by_column;
    bool order_desc = false;

    std::optional<std::size_t> limit;
};

struct QueryResult {
    std::vector<std::string> header;
    std::vector<std::vector<std::string>> rows;
};

class CsvTable {
public:
    void load_from_file(const std::string& path);
    const std::vector<std::string>& header() const;
    const std::vector<std::vector<std::string>>& rows() const;

private:
    std::vector<std::string> header_;
    std::vector<std::vector<std::string>> rows_;
};

class QueryEngine {
public:
    Query parse_query(const std::string& query_text) const;
    QueryResult execute(const CsvTable& table, const Query& query) const;
};

}  // namespace csvdb

#endif

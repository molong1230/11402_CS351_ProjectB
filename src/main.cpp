#include "csv_db.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace {

std::string join_csv_row(const std::vector<std::string>& row) {
    std::ostringstream os;
    for (std::size_t i = 0; i < row.size(); ++i) {
        if (i > 0) {
            os << ',';
        }
        os << row[i];
    }
    return os.str();
}

void print_usage() {
    std::cout << "Usage: csvdb_cli --csv <file.csv> --query \"SELECT ...\" [--output result.csv]\n";
}

}  // namespace

int main(int argc, char** argv) {
    try {
        std::string csv_path;
        std::string query_text;
        std::string output_path;

        for (int i = 1; i < argc; ++i) {
            const std::string arg = argv[i];
            if (arg == "--csv" && i + 1 < argc) {
                csv_path = argv[++i];
            } else if (arg == "--query" && i + 1 < argc) {
                query_text = argv[++i];
            } else if (arg == "--output" && i + 1 < argc) {
                output_path = argv[++i];
            } else if (arg == "--help") {
                print_usage();
                return 0;
            } else {
                throw std::runtime_error("Unknown or incomplete argument: " + arg);
            }
        }

        if (csv_path.empty() || query_text.empty()) {
            print_usage();
            return 1;
        }

        csvdb::CsvTable table;
        table.load_from_file(csv_path);

        csvdb::QueryEngine engine;
        const csvdb::Query query = engine.parse_query(query_text);
        const csvdb::QueryResult result = engine.execute(table, query);

        std::ostringstream out;
        out << join_csv_row(result.header) << '\n';
        for (const auto& row : result.rows) {
            out << join_csv_row(row) << '\n';
        }

        if (!output_path.empty()) {
            std::ofstream fout(output_path);
            if (!fout.is_open()) {
                throw std::runtime_error("Cannot write output file: " + output_path);
            }
            fout << out.str();
        } else {
            std::cout << out.str();
        }

        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        return 1;
    }
}

#include "csv_db.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

namespace {

void expect(bool condition, const std::string& message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

}  // namespace

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: csvdb_tests <sample_csv_path>\\n";
        return 1;
    }

    const std::string csv_path = argv[1];

    try {
        csvdb::CsvTable table;
        table.load_from_file(csv_path);

        csvdb::QueryEngine engine;

        {
            const auto query = engine.parse_query("SELECT name,score WHERE class=A ORDER BY score DESC LIMIT 2");
            const auto result = engine.execute(table, query);
            expect(result.header.size() == 2, "Header size should be 2");
            expect(result.rows.size() == 2, "Should return two rows");
            expect(result.rows[0][0] == "Eve", "Top score student in class A should be Eve");
            expect(result.rows[1][0] == "Alice", "Second score student in class A should be Alice");
        }

        {
            const auto query = engine.parse_query("SELECT COUNT(*) WHERE class=B");
            const auto result = engine.execute(table, query);
            expect(result.header.size() == 1, "COUNT header size should be 1");
            expect(result.rows.size() == 1, "COUNT should return single row");
            expect(result.rows[0][0] == "2", "class B should have 2 records");
        }

        std::cout << "All tests passed.\\n";
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "Test failed: " << ex.what() << '\n';
        return 1;
    }
}

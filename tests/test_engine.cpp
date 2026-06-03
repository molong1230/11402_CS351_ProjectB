#include "csv_db.hpp"

#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {

void expect(bool condition, const std::string& message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

void expect_throw_contains(const std::function<void()>& action, const std::string& substring, const std::string& label) {
    try {
        action();
        throw std::runtime_error(label + ": expected exception was not thrown");
    } catch (const std::runtime_error& ex) {
        const std::string message = ex.what();
        if (message.find(substring) == std::string::npos) {
            throw std::runtime_error(label + ": unexpected message: " + message);
        }
    }
}

void test_happy_paths(const csvdb::CsvTable& table, csvdb::QueryEngine& engine) {
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

    {
        const auto query = engine.parse_query("SELECT id,name");
        const auto result = engine.execute(table, query);
        expect(result.header.size() == 2, "Projection header size should be 2");
        expect(result.rows.size() == 5, "Projection should return all rows");
        expect(result.header[0] == "id", "First projected column should be id");
        expect(result.header[1] == "name", "Second projected column should be name");
    }

    {
        const auto query = engine.parse_query("SELECT * WHERE class=A ORDER BY name ASC");
        const auto result = engine.execute(table, query);
        expect(result.header.size() == 4, "SELECT * header size should be 4");
        expect(result.rows.size() == 3, "class A should have 3 records");
        expect(result.rows[0][1] == "Alice", "Ascending name order should start with Alice");
    }
}

void test_query_errors(csvdb::QueryEngine& engine, const csvdb::CsvTable& table) {
    expect_throw_contains(
        [&]() { engine.parse_query("SELECT * WHERE class"); },
        "WHERE must use equality",
        "Malformed WHERE");

    expect_throw_contains(
        [&]() {
            const auto query = engine.parse_query("SELECT unknown");
            engine.execute(table, query);
        },
        "Unknown SELECT column",
        "Unknown SELECT column");

    expect_throw_contains(
        [&]() { engine.parse_query("UPDATE name"); },
        "Query must start with SELECT",
        "Unsupported query prefix");

    expect_throw_contains(
        [&]() { engine.parse_query("SELECT name ORDER BY score UP"); },
        "ORDER BY direction must be ASC or DESC",
        "Invalid ORDER BY direction");
}

void test_csv_errors(const std::string& invalid_csv_path, const std::string& missing_csv_path) {
    csvdb::CsvTable table;
    expect_throw_contains(
        [&]() { table.load_from_file(invalid_csv_path); },
        "different column count",
        "Invalid CSV row shape");

    expect_throw_contains(
        [&]() { table.load_from_file(missing_csv_path); },
        "Cannot open CSV file",
        "Missing CSV file");
}

}  // namespace

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: csvdb_tests <sample_csv_path> <invalid_csv_path>\n";
        return 1;
    }

    const std::string csv_path = argv[1];
    const std::string invalid_csv_path = argv[2];

    try {
        csvdb::CsvTable table;
        table.load_from_file(csv_path);

        csvdb::QueryEngine engine;
        test_happy_paths(table, engine);
        test_query_errors(engine, table);
        test_csv_errors(invalid_csv_path, invalid_csv_path + ".missing");

        std::cout << "All engine tests passed.\n";
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "Test failed: " << ex.what() << '\n';
        return 1;
    }
}

# Project B - CSV Mini Database and Query Engine

## Description
Project B aims to build a lightweight database system that stores data in CSV files and provides a mini query engine for retrieving and processing records. The project simulates core database behavior in a simplified environment so that students can understand how query systems work from parsing to execution.

Your system should load CSV files as tables, interpret user queries, execute operations on in-memory data, and return clear results. Expected query capabilities include selecting columns, filtering rows with conditions, sorting output, and performing basic aggregation.

## Scope and Learning Objectives
- Parse CSV files into structured tables with schema awareness.
- Design and implement a small query interface (SQL-like or command-based).
- Build an execution pipeline that applies projection, selection, ordering, and aggregation.
- Handle invalid input gracefully, including malformed CSV, type mismatch, and unsupported queries.
- Provide readable output and meaningful error messages.

## Expected Outcome
A functional and modular CSV mini database and query engine that demonstrates fundamental DBMS concepts and can serve as a foundation for more advanced database features.

## Build and Run

### Prerequisites
- C++ compiler (g++/clang++/MSVC)
- CMake 3.16+

### Build
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

### Run Tests
```bash
ctest --test-dir build --output-on-failure
```

### Run CLI Example
Linux/macOS:
```bash
./build/csvdb_cli --csv data/sample_students.csv --query "SELECT name,score WHERE class=A ORDER BY score DESC LIMIT 2"
```

Windows PowerShell:
```powershell
.\build\csvdb_cli.exe --csv data\sample_students.csv --query "SELECT name,score WHERE class=A ORDER BY score DESC LIMIT 2"
```

## Project Structure
- docs/00_intended_use.md
- docs/01_plan.md
- docs/02_SRS.md
- docs/03_SDS.md
- docs/04_test_plan.md
- docs/05_acceptance_tests.md
- docs/06_traceability.md
- docs/07_deploy.md
- docs/08_known_issues.md
- include/
- src/
- tests/
- data/sample_students.csv
- .github/workflows/ci.yml


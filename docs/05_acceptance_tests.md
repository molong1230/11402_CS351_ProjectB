# 05 Acceptance Tests - CSV Mini Database and Query Engine

## 1. Purpose
Acceptance tests validate the system as a black-box CLI tool from a user perspective.

## 2. Preconditions
- Repository cloned.
- C++ compiler and CMake installed.
- Build completed successfully.
- data/sample_students.csv exists.

## 3. Scenarios
### AT-1 Basic end-to-end query
- Command:
  - ./build/csvdb_cli --csv data/sample_students.csv --query "SELECT name,score WHERE class=A ORDER BY score DESC LIMIT 2"
- Expected:
  - Header includes name,score.
  - Returns exactly 2 rows.
  - First row is Eve,97 and second row is Alice,91.

### AT-2 Aggregate count query
- Command:
  - ./build/csvdb_cli --csv data/sample_students.csv --query "SELECT COUNT(*) WHERE class=B"
- Expected:
  - Header includes count.
  - Result value is 2.

### AT-3 Output to file
- Command:
  - ./build/csvdb_cli --csv data/sample_students.csv --query "SELECT id,name" --output result.csv
- Expected:
  - result.csv is created.
  - File contains header and all rows for id,name.

### AT-4 Invalid query handling
- Command:
  - ./build/csvdb_cli --csv data/sample_students.csv --query "SELECT unknown"
- Expected:
  - Non-zero exit code.
  - Clear error message about unknown column.

## 4. Acceptance Decision
The project is accepted when all scenarios pass with expected outputs and error behavior.

# 04 Test Plan - CSV Mini Database and Query Engine

## 1. Test Objectives
- Verify core functional requirements for CSV loading and query execution.
- Verify deterministic behavior and error handling.
- Ensure CLI workflow is reproducible.

## 2. Test Levels
1. Unit tests
- Query parser behavior.
- Query execution behavior (projection, filter, order, aggregate, limit).

2. Integration tests
- CSV load + parse + execute end-to-end in process.

3. CLI smoke tests
- Execute binary using documented command and inspect output.

## 3. Test Scope by Requirement
- FR-1, FR-2: CSV load and schema consistency.
- FR-3: Query parser syntax handling.
- FR-4: SELECT projection.
- FR-5: WHERE equality filter.
- FR-6: ORDER BY ASC/DESC.
- FR-7: COUNT(*).
- FR-8: LIMIT.
- FR-9: CLI output formatting.
- FR-10: Invalid input errors and non-zero exit code.

## 4. Test Data
- File: data/sample_students.csv
- Dataset has two classes and varied scores for order/filter verification.

## 5. Planned Test Cases
1. Valid query with where/order/limit
- Input: SELECT name,score WHERE class=A ORDER BY score DESC LIMIT 2
- Expected: two rows sorted by score descending.

2. Aggregate query
- Input: SELECT COUNT(*) WHERE class=B
- Expected: count = 2.

3. Unknown column
- Input: SELECT unknown
- Expected: semantic query error.

4. Malformed where
- Input: SELECT * WHERE class
- Expected: query syntax error.

5. Invalid CSV shape
- Input: csv with mismatched column counts
- Expected: CSV format error.

## 6. Execution Commands
- cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
- cmake --build build
- ctest --test-dir build --output-on-failure

## 7. Exit Criteria
- All implemented tests pass.
- No blocker-level defects in core query flow.
- Critical requirements FR-1 to FR-10 have at least one mapped test.

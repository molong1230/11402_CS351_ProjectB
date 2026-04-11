# 02 SRS - Software Requirements Specification

## 1. System Overview
The system reads a CSV file as a table and executes a mini query command through CLI. Query results are shown on stdout or written to an output file.

## 2. External Interface
### 2.1 CLI
Proposed command format:
- app --csv <input.csv> --query "<query_text>" [--output <result.csv>]

### 2.2 Query Language Subset
Supported clauses (in this project baseline):
- SELECT <columns | * | COUNT(*)>
- optional WHERE <column>=<value>
- optional ORDER BY <column> [ASC|DESC]
- optional LIMIT <n>

Example:
- SELECT name,score WHERE class=A ORDER BY score DESC LIMIT 3

## 3. Functional Requirements
FR-1 CSV Loading
- The system shall load a CSV file from a user-provided path.
- The first row shall be interpreted as column headers.

FR-2 Schema Validation
- The system shall validate that each row has the same column count as the header.
- The system shall report an error when row shape is invalid.

FR-3 Query Parsing
- The system shall parse supported query clauses and build an internal query representation.
- The system shall reject malformed query strings with a deterministic error.

FR-4 Projection
- The system shall return only requested columns for SELECT <col_list>.
- The system shall support SELECT * for all columns.

FR-5 Selection
- The system shall filter rows using equality condition in WHERE clause.

FR-6 Ordering
- The system shall sort output rows by ORDER BY column in ASC or DESC order.

FR-7 Aggregation
- The system shall support COUNT(*) and return a single-row result.

FR-8 Limit
- The system shall limit output row count when LIMIT is specified.

FR-9 CLI Output
- The system shall print a CSV-formatted result table to stdout by default.
- The system shall write results to file when --output is provided.

FR-10 Error Handling
- The system shall return non-zero exit code on failure.
- The system shall provide clear error messages for invalid CSV, query syntax, unknown column, and file IO errors.

## 4. Non-Functional Requirements
NFR-1 Determinism
- Given identical input CSV and query, output shall be identical.

NFR-2 Portability
- The project shall build on standard C++23 toolchains using CMake.

NFR-3 Reproducibility
- Build and test commands shall work from a clean clone with documented steps.

NFR-4 Maintainability
- Module boundaries shall separate parsing, execution, and CLI layers.

NFR-5 Robustness
- Invalid inputs shall not crash the process; errors shall be handled gracefully.

## 5. Error Handling Expectations
- Missing file path: report input argument error.
- Nonexistent CSV file: report file open failure.
- Header/row mismatch: report CSV format error.
- Unknown column in SELECT/WHERE/ORDER BY: report semantic query error.
- Invalid LIMIT value: report query parse error.

## 6. Acceptance Criteria Summary
AC-1 Build command completes successfully on clean setup.
AC-2 At least one end-to-end query command returns expected output.
AC-3 FR-1 through FR-10 are covered by tests or acceptance scenarios.
AC-4 Failure scenarios produce deterministic error messages and non-zero exit code.

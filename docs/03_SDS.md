# 03 SDS - Software Design Specification

## 1. Design Goals
- Keep implementation modular and traceable to requirements.
- Keep grammar and execution scope small and deterministic.
- Keep CLI usage straightforward for grading and reproducibility.

## 2. High-Level Architecture
1. CLI Layer
- Parses command-line arguments.
- Calls parser/execution flow.
- Handles output formatting and exit codes.

2. Data Layer
- Loads CSV file into in-memory table representation.
- Stores header and rows.

3. Query Parser Layer
- Converts query text into internal Query object.
- Validates clause format and basic syntax.

4. Execution Engine Layer
- Applies operators in sequence:
  projection, selection, ordering, aggregation, limit.
- Produces QueryResult object.

## 3. Proposed Modules
1. CsvTable
- Responsibilities:
  load file, parse lines, validate shape.
- Inputs: file path
- Outputs: header and rows

2. Query
- Responsibilities:
  hold parsed query intent.
- Key fields:
  selected columns, where condition, order config, aggregation mode, limit.

3. QueryEngine
- Responsibilities:
  parse query text and execute on CsvTable.
- Main methods:
  parse_query(query_text), execute(table, query)

4. ResultFormatter
- Responsibilities:
  render query result as CSV text to stdout/file.

## 4. Data Structures
- Table header: vector<string>
- Table rows: vector<vector<string>>
- Column index map: unordered_map<string, size_t>
- Query object:
  - select_columns: vector<string>
  - count_star: bool
  - where_column/where_value: optional<string>
  - order_by_column: optional<string>
  - order_desc: bool
  - limit: optional<size_t>

## 5. Query Processing Flow
1. Validate CLI arguments.
2. Load CSV into CsvTable.
3. Parse query string into Query object.
4. Resolve column names to indexes.
5. Execute operators in deterministic order:
- WHERE filter
- ORDER BY sort
- SELECT projection or COUNT(*)
- LIMIT truncation
6. Render and emit output.

## 6. Error Model
Error categories:
- ArgumentError: missing or invalid CLI args
- CsvFormatError: malformed CSV rows
- QuerySyntaxError: malformed query text
- QuerySemanticError: unknown columns or unsupported operation
- IOError: file read/write failure

Behavior:
- Any error returns non-zero process exit code.
- Error message includes category and concise cause.

## 7. Key Design Decisions
1. In-memory execution
- Reason: data size is course-scale; implementation is simpler and testable.

2. Equality-only WHERE baseline
- Reason: keeps parser and semantics manageable for project scope.

3. Single-table query baseline
- Reason: avoids join complexity and keeps traceability clear.

4. Deterministic output
- Reason: required for reliable grading and repeatable tests.

## 8. Mapping to Requirements
- FR-1, FR-2 -> CsvTable
- FR-3 -> Query parser in QueryEngine
- FR-4, FR-5, FR-6, FR-7, FR-8 -> Execution pipeline in QueryEngine
- FR-9, FR-10 -> CLI Layer + ResultFormatter + Error Model

## 9. Testability Considerations
- Keep parser and execution methods callable without CLI.
- Use fixed CSV fixtures for deterministic test outputs.
- Ensure each FR has at least one direct test mapping.

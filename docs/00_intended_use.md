# 00 Intended Use - CSV Mini Database and Query Engine

## 1. Problem Statement
This project builds a small database-like system that reads tabular data from CSV files and executes simple query commands from users. The goal is to provide a lightweight, local, and reproducible tool for filtering and analyzing structured data without setting up a full DBMS.

## 2. Target Users
- CS351 course students implementing and testing database fundamentals.
- Instructors and TAs who need a reproducible command-line workflow for grading.
- Developers who want a compact reference implementation of query processing concepts.

## 3. Intended Usage Scenarios
- Load one CSV file as a table and run a query through a command-line interface.
- Perform core operations: column selection, row filtering, ordering, and basic aggregation.
- Export query output for inspection or downstream processing.

## 4. Inputs and Outputs
### Input
- CSV file path (UTF-8 text, comma-separated values, first row as header).
- Query command string (SQL-like mini syntax defined in SRS).
- Optional output path for saving query results.

### Output
- Query result table printed to stdout or written to a file.
- Deterministic error messages for invalid CSV format, unknown columns, malformed query, and unsupported operations.

## 5. Execution Environment
- Operating systems: Windows, Linux, or macOS.
- Language and toolchain baseline: C++23 and CMake.
- Local execution through terminal/CLI; no server deployment required.
- Build and test should run on a clean clone with documented commands.

## 6. Success Criteria
The project is considered successful when:
1. A user can build the project from scratch using documented commands.
2. A user can execute at least one end-to-end query scenario successfully.
3. Core query capabilities (select, where, order, aggregate) behave as specified.
4. Invalid inputs produce clear and repeatable error messages.
5. Test execution demonstrates requirement-level verification.

## 7. Non-Goals
- No transaction management (ACID) or concurrency control.
- No multi-user authentication/authorization features.
- No distributed storage or networked database service.
- No full SQL compatibility.
- No GUI requirement in this project stage.

## 8. Constraints and Assumptions
- Time is limited to one course project cycle.
- Implementation should prioritize readability and traceability over advanced optimization.
- Dependency policy should stay lightweight and course-friendly.
- Input data is assumed to be moderately sized for in-memory processing.

## 9. Scope Boundary Summary
In scope:
- CSV parsing and table loading.
- Mini query parsing and execution.
- CLI interaction and result output.
- Testing, documentation, and traceability artifacts.

Out of scope:
- Enterprise database features and production-hardening concerns.

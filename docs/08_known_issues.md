# 08 Known Issues and Limitations

## 1. Current Limitations
- Query language supports a limited SQL-like subset only.
- WHERE currently supports equality condition only.
- Single-table CSV query only; no join support.
- Type system is string-based for baseline behavior.

## 2. Deferred Features
- Extended operators (<, >, <=, >=, !=).
- Multiple conditions with AND/OR.
- Group-by and additional aggregations (SUM, AVG, MIN, MAX).
- More robust CSV dialect support.

## 3. Known Risks
- Very large CSV files may increase memory usage due to in-memory execution.
- String-based sorting may not match numeric sorting expectations in all cases.

## 4. Reporting Guidance
When reporting an issue, include:
- Input CSV sample
- Query command
- Expected output
- Actual output/error
- Environment info (OS/compiler/CMake version)

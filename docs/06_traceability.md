# 06 Traceability Matrix

## 1. Traceability Chain
Intended Use -> SRS Requirement -> SDS Module/Section -> Test Evidence

## 2. Matrix
| Requirement | SDS Mapping | Verification Test | Acceptance Scenario |
| --- | --- | --- | --- |
| FR-1 CSV Loading | CsvTable module | Unit/Integration: load sample CSV | AT-1, AT-2 |
| FR-2 Schema Validation | CsvTable validation logic | Invalid CSV shape test | AT-4 (error behavior style) |
| FR-3 Query Parsing | QueryEngine parse_query | Parser valid/invalid tests | AT-1, AT-4 |
| FR-4 Projection | QueryEngine execute projection | SELECT column tests | AT-1, AT-3 |
| FR-5 Selection | QueryEngine where filter | WHERE equality tests | AT-1 |
| FR-6 Ordering | QueryEngine sorting path | ORDER BY tests | AT-1 |
| FR-7 Aggregation | COUNT(*) path | COUNT tests | AT-2 |
| FR-8 Limit | LIMIT path | LIMIT tests | AT-1 |
| FR-9 CLI Output | main.cpp output flow | CLI smoke test | AT-1, AT-3 |
| FR-10 Error Handling | error model in parser/CLI | invalid query/input tests | AT-4 |

## 3. Notes
- FR IDs are defined in docs/02_SRS.md.
- Design mapping is defined in docs/03_SDS.md.
- Test planning details are in docs/04_test_plan.md and docs/05_acceptance_tests.md.

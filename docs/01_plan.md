# 01 Plan - CSV Mini Database and Query Engine

## 1. Objective
Deliver a runnable and testable CSV mini database and query engine that supports select, filter, order, and basic aggregation through a CLI workflow.

## 2. Scope for This Plan
In scope:
- Documentation package (SRS and SDS)
- Core implementation (CSV parser, query parser, execution engine, CLI)
- Verification tests and acceptance tests
- Traceability, deployment notes, and known issues

Out of scope:
- Full SQL compatibility
- Multi-user concurrency
- Persistence beyond CSV files

## 3. Work Breakdown Structure
1. WP-1 Documentation Foundation
- Create and refine intended use, plan, SRS, SDS
- Ensure requirement IDs and terminology are consistent

2. WP-2 Core System Skeleton
- Set up CMake, include/src/tests layout, and executable target
- Add sample data for repeatable tests

3. WP-3 Query Engine Implementation
- Implement CSV load and schema validation
- Implement query grammar parsing
- Implement execution operators: projection, selection, ordering, aggregation

4. WP-4 CLI and Error Model
- Implement command-line arguments
- Define deterministic error messages and exit behavior

5. WP-5 Verification and Validation
- Unit tests, integration tests, invalid input tests
- Acceptance scenarios with expected outputs

6. WP-6 Delivery Quality
- Traceability matrix
- Deploy guide for clean clone
- Known issues and CI checks

## 4. Milestones
1. M1 - Documentation Complete
- Done when docs/01_plan.md, docs/02_SRS.md, docs/03_SDS.md are committed and internally consistent.

2. M2 - MVP Runnable
- Done when project builds and one end-to-end query command runs successfully.

3. M3 - Quality and Submission Ready
- Done when tests, traceability, deployment notes, and known issues are complete.

## 5. Task Ownership Template
Use the following fields for each Jira item:
- Owner
- Branch name
- Planned start/end date
- Acceptance criteria
- PR link
- Status (To Do / In Progress / In Review / Done)

## 6. Branch and PR Strategy
- One Story corresponds to one feature branch and one focused PR.
- Branch naming convention: feature/<JIRA_KEY>-<short-topic>
- Commit title convention: <JIRA_KEY> <action>
- PR title convention: <JIRA_KEY> <deliverable>

## 7. Risks and Mitigation
1. Risk: Requirement drift
- Mitigation: Freeze SRS IDs before large coding begins.

2. Risk: Parser complexity expands beyond scope
- Mitigation: Restrict grammar to the SRS-defined subset.

3. Risk: Test gaps discovered late
- Mitigation: Add tests per feature increment and link tests to FR IDs.

4. Risk: Build reproducibility issues
- Mitigation: Verify deployment steps on a clean clone before final merge.

## 8. Definition of Done for This Project
A deliverable is done only if:
- Document/code changes are committed with Jira key
- Related tests pass locally
- PR includes acceptance evidence
- Jira status is updated to match engineering state

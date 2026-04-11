# 07 Deploy and Run from Scratch

## 1. Environment Checklist
- Git installed.
- C++ compiler installed (g++/clang++/MSVC).
- CMake 3.16+ installed.
- Repository cloned successfully.

## 2. Clean Setup Procedure
1. Clone repository.
2. Enter repository root.
3. Configure build.
4. Build executable and tests.
5. Run tests.
6. Execute one CLI example.

## 3. Commands
### Windows PowerShell
- cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
- cmake --build build
- ctest --test-dir build --output-on-failure
- .\build\csvdb_cli.exe --csv data\sample_students.csv --query "SELECT name,score WHERE class=A ORDER BY score DESC LIMIT 2"

### Linux/macOS
- cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
- cmake --build build
- ctest --test-dir build --output-on-failure
- ./build/csvdb_cli --csv data/sample_students.csv --query "SELECT name,score WHERE class=A ORDER BY score DESC LIMIT 2"

## 4. Packaging Notes
- Current deliverable is source + CMake build flow.
- No binary release artifact is required at this stage.

## 5. Troubleshooting
- If cmake command is not found, install CMake and add it to PATH.
- If tests fail, verify sample CSV path and rebuild from clean build directory.

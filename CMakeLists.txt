cmake_minimum_required(VERSION 3.16)
project(CSVMiniDB VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(csvdb STATIC src/csv_db.cpp)
target_include_directories(csvdb PUBLIC include)

add_executable(csvdb_cli src/main.cpp)
target_link_libraries(csvdb_cli PRIVATE csvdb)

enable_testing()

add_executable(csvdb_tests tests/test_engine.cpp)
target_link_libraries(csvdb_tests PRIVATE csvdb)

add_test(
    NAME csvdb_unit_tests
    COMMAND csvdb_tests ${CMAKE_SOURCE_DIR}/data/sample_students.csv
)

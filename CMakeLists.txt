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

set(SAMPLE_CSV "${CMAKE_SOURCE_DIR}/data/sample_students.csv")
set(INVALID_CSV "${CMAKE_SOURCE_DIR}/data/invalid_row_shape.csv")
set(AT3_OUTPUT "${CMAKE_BINARY_DIR}/at3_result.csv")

add_test(
    NAME engine_tests
    COMMAND csvdb_tests ${SAMPLE_CSV} ${INVALID_CSV}
)

add_test(
    NAME cli_at1_basic_query
    COMMAND csvdb_cli --csv ${SAMPLE_CSV} --query "SELECT name,score WHERE class=A ORDER BY score DESC LIMIT 2"
)
set_tests_properties(cli_at1_basic_query PROPERTIES
    PASS_REGULAR_EXPRESSION "Eve,97"
)

add_test(
    NAME cli_at2_count_query
    COMMAND csvdb_cli --csv ${SAMPLE_CSV} --query "SELECT COUNT(*) WHERE class=B"
)
set_tests_properties(cli_at2_count_query PROPERTIES
    PASS_REGULAR_EXPRESSION "count[\r\n]+2"
)

add_test(
    NAME cli_at3_output_file
    COMMAND csvdb_cli --csv ${SAMPLE_CSV} --query "SELECT id,name" --output ${AT3_OUTPUT}
)

add_test(
    NAME cli_at3_verify_output
    COMMAND ${CMAKE_COMMAND} -DFILE=${AT3_OUTPUT} -P ${CMAKE_SOURCE_DIR}/tests/verify_output.cmake
)
set_tests_properties(cli_at3_verify_output PROPERTIES DEPENDS cli_at3_output_file)

add_test(
    NAME cli_at4_invalid_query
    COMMAND csvdb_cli --csv ${SAMPLE_CSV} --query "SELECT unknown"
)
set_tests_properties(cli_at4_invalid_query PROPERTIES WILL_FAIL TRUE)

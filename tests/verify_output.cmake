if(NOT DEFINED FILE)
    message(FATAL_ERROR "FILE variable is required")
endif()

if(NOT EXISTS "${FILE}")
    message(FATAL_ERROR "Output file does not exist: ${FILE}")
endif()

file(READ "${FILE}" CONTENT)
if(NOT CONTENT MATCHES "id,name")
    message(FATAL_ERROR "Output file is missing id,name header")
endif()

file(STRINGS "${FILE}" LINES)
list(LENGTH LINES LINE_COUNT)
if(NOT LINE_COUNT EQUAL 6)
    message(FATAL_ERROR "Expected 6 lines in output file, got ${LINE_COUNT}")
endif()

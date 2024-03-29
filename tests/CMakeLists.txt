cmake_minimum_required(VERSION 3.15)
project(MyProjectTest LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/archive)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../)

set(OUT_NAME test_matrix_oop)
add_compile_definitions(FOR_TEST)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -Wall -fprofile-arcs -ftest-coverage -fsanitize=address")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -Wall -fprofile-arcs -ftest-coverage -fsanitize=address")

# find_package(GTest REQUIRED) # !!!
find_package(Threads REQUIRED)

include_directories(./googletest/googletest/include)
add_subdirectory(./googletest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(HEADERS
    includes/test_matrix_oop.h
    ../lib/s21_matrix_oop.h
)

set(3RD_LIBS gtest pthread)
set(SOURCES
    srcs/test_matrix_oop.cpp
)

add_executable(${OUT_NAME} ${SOURCES} ${HEADERS})

enable_testing()

include_directories(
    ./include
    ../lib/
    # ${GTEST_INCLUDE_DIRS} # !!!
)

target_include_directories(${OUT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/includes
    ${CMAKE_CURRENT_LIST_DIR}/../
)


target_link_libraries(${OUT_NAME}
    PUBLIC
    # ${GTEST_LIBRARIES}  # !!!
    Threads::Threads
    ${CMAKE_CURRENT_LIST_DIR}/../lib/s21_matrix_oop_gcov.a
    ${3RD_LIBS}
)

add_test(NAME ${OUT_NAME} COMMAND ${OUT_NAME})

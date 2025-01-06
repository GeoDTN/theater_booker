cmake_minimum_required(VERSION 3.30)
project(theater_booker)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++2a")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        set(CXX_FILESYSTEM_LIBRARIES "stdc++fs")
endif()

find_package(GTest REQUIRED)

include_directories(
    ../include
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

# Add source files under test
set(UNIT_TEST_SRC_FILES "${${CMAKE_PROJECT_NAME}_SRC_FILES}")

add_executable(${PROJECT_NAME}_tests
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/theater_booker_tests.cpp
    ../src/theater_booker.cpp

    )

include(GoogleTest)
target_link_libraries(
    ${CMAKE_PROJECT_NAME}_tests
    pthread
    ${GTEST_LIBRARIES}
    ${GMOCK_LIBRARIES}
    GTest::GTest
    stdc++fs
)

target_include_directories(${CMAKE_PROJECT_NAME}_tests
                           PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR}/inc
)
 
gtest_discover_tests(${PROJECT_NAME}_tests)

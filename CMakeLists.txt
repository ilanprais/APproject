cmake_minimum_required(VERSION 3.0.0)
project(search_tester VERSION 0.1.0)

include(CTest)
set(C_STANDARD C99)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -pedantic -Werror)
enable_testing()

include_directories(${CMAKE_SOURCE_DIR})
link_directories(${CMAKE_SOURCE_DIR})
add_executable(search_tester tester.cpp SearchResult.cpp
Graph.cpp Matrix.cpp ErrorCode.cpp)
target_link_libraries(search_tester matrix)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

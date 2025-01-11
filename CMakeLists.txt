cmake_minimum_required(VERSION 3.12)
project(labwork9)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(ITMO_Adaptors)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC adaptors)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

enable_testing()
add_subdirectory(tests)
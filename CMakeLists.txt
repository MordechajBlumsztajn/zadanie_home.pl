cmake_minimum_required(VERSION 3.0.0)
project(Linux_Process_Informer VERSION 1.0.0)

set(CMAKE_C_FLAGS "-Wall -Wextra -std=c99")

add_subdirectory(utilities)
add_subdirectory(input_processor)
add_subdirectory(process_info)

add_executable(PIDinfo main.c)

target_link_libraries(PIDinfo utilities input_processor process_informer)
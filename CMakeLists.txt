cmake_minimum_required(VERSION 3.0.0)
project(Linux_Process_PID_Displayer VERSION 1.0.0)

set(CMAKE_C_FLAGS "-Wall -Wextra -std=c99")

add_subdirectory(utilities)
add_subdirectory(input_processor)
add_subdirectory(process_info)

add_executable(pid_displayer main.c)

target_link_libraries(pid_displayer utilities input_processor process_informer)
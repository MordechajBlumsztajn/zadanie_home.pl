cmake_minimum_required(VERSION 3.0.0)
project(Linux_Process_PID_Displayer VERSION 1.0.0)

set(CMAKE_C_FLAGS "-Wall -Wextra -std=c99")

add_executable(pid_displayer
main.c)
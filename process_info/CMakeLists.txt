add_library(process_informer src/process_info.c)

target_include_directories(process_informer PUBLIC include PRIVATE ${CMAKE_SOURCE_DIR}/utilities/include)
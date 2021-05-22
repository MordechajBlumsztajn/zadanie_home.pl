add_library(input_processor src/input_processor.c)

target_include_directories(input_processor PUBLIC include PRIVATE ${CMAKE_SOURCE_DIR}/utilities/include)
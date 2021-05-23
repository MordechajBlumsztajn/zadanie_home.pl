#ifndef PID_DISPLAYER_INPUT_PROCESSOR_H
#define PID_DISPLAYER_INPUT_PROCESSOR_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <getopt.h>

#include "utilities.h"

void copy_option_argument(char** destination, enum OPTS_WITH_ARGS_INDEX_ORDER index, char* source);
FC parse_input(int argc, char* argv[], char* optsargs[], FC flags);
FC check_for_mandatory_option(FC flags);
FC check_for_option_exclusivity(FC flags);
FC check_for_non_optional_arguments(int argc, char* argv[], FC flags);
bool error_occurred(FC flags);
char** allocate_memory_for_option_arguments(unsigned args_count);
void deallocate_option_arguments_memory(char** optargs, unsigned args_count);

#endif
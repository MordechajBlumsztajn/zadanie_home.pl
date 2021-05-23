#ifndef PID_DISPLAYER_PROCESS_INFO_H
#define PID_DISPLAYER_PROCESS_INFO_H

#include <stdio.h>
#include <stdbool.h>

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>

FILE* open_file_to_write_if_requested(char* filename);
void close_file_if_needed(FILE* stream);
void print_all_procs_info(char* filename);
void print_proc_name(char* pid, char* filename);
void print_proc_pid(char* process_name, char* filename);

#endif
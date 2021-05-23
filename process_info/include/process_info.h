#ifndef PID_DISPLAYER_PROCESS_INFO_H
#define PID_DISPLAYER_PROCESS_INFO_H

#include <stdio.h>
#include <stdbool.h>

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>

FILE* open_file_to_write_if_requested(bool write_to_file, char* filename);
void close_file_if_needed(bool write_to_file, FILE* stream);
void print_all_procs_info(bool write_to_file, char* filename);
void print_proc_name(char* pid, bool write_to_file, char* filename);
void print_proc_pid(char* process_name, bool write_to_file, char* filename);

#endif
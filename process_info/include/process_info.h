#ifndef PID_DISPLAYER_PROCESS_INFO_H
#define PID_DISPLAYER_PROCESS_INFO_H

#include <stdio.h>
#include <stdbool.h>

#include <string.h>
#include <dirent.h>

#include "utilities.h"

void print_all_procs_info(char* filename);
void print_proc_name_from_pid(char* pid, char* filename);
void print_proc_pid_from_name(char* process_name, char* filename);

#endif
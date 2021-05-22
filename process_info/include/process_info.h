#ifndef PID_DISPLAYER_PROCESS_INFO_H
#define PID_DISPLAYER_PROCESS_INFO_H

#include <stdio.h>

void print_all_processes_info(FILE* stream, char* filename);
void print_process_name(char* pid, FILE* stream, char* filename);
void print_process_pid(char* process_name, FILE* stream, char* filename);

#endif
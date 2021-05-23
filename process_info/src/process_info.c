#include "process_info.h"

FILE* open_file_if_requested(bool write_to_file, char* filename)
{
    return NULL;
}

void close_file_if_needed(bool write_to_file, FILE* stream)
{
    printf("\n");

    // if (write_to_file && !stream)
    // {
    //     fclose(stream);
    // }
}

// option -a
void print_all_processes_info(bool write_to_file, char* filename)
{
    FILE* stream = open_file_if_requested(write_to_file, filename);

    printf("-a ");

    close_file_if_needed(write_to_file, stream);
}

// option -u
void print_process_name(char* pid, bool write_to_file, char* filename)
{
    FILE* stream = open_file_if_requested(write_to_file, filename);

    printf("-u %s ", pid);
    
    close_file_if_needed(write_to_file, stream);
}

// option -n
void print_process_pid(char* process_name, bool write_to_file, char* filename)
{
    FILE* stream = open_file_if_requested(write_to_file, filename);

    printf("-n %s ", process_name);
    
    close_file_if_needed(write_to_file, stream);
}
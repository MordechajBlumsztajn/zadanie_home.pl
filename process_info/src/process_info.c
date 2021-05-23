#include "process_info.h"

FILE* open_file_to_write_if_requested(bool write_to_file, char* filename)
{
    const char* const mode = "w";
    FILE* stream = stdout;

    if (write_to_file)
    {
        stream = fopen(filename, mode);
        if (NULL == stream)
        {
            fprintf(stderr, "critical error: %s\n", strerror(errno));
            exit(errno);
        }
    }

    return stream;
}

void close_file_if_needed(bool write_to_file, FILE* stream)
{
    if (write_to_file && stream != NULL && stream != stdout)
    {
        fclose(stream);
    }
}

// option -a
void print_all_processes_info(bool write_to_file, char* filename)
{
    FILE* stream = open_file_to_write_if_requested(write_to_file, filename);

    fprintf(stream, "-a\n");

    close_file_if_needed(write_to_file, stream);
}

// option -u
void print_process_name(char* pid, bool write_to_file, char* filename)
{
    FILE* stream = open_file_to_write_if_requested(write_to_file, filename);

    fprintf(stream, "-u %s\n", pid);
    
    close_file_if_needed(write_to_file, stream);
}

// option -n
void print_process_pid(char* process_name, bool write_to_file, char* filename)
{
    FILE* stream = open_file_to_write_if_requested(write_to_file, filename);

    fprintf(stream, "-n %s\n", process_name);
    
    close_file_if_needed(write_to_file, stream);
}
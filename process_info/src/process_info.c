#include "process_info.h"

const char* const proc_dir = "/proc";


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

bool is_string_a_number(char* str)
{
    bool result = strlen(str)? true : false;
    int i = 0;
    while(str[i])
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            i++;
        }
        else
        {
            result = false;
            break;
        }
    }
    return result;
}

// option -a
void print_all_procs_info(bool write_to_file, char* filename)
{
    FILE* stream = open_file_to_write_if_requested(write_to_file, filename);

    struct dirent *ptr_dirent;
    DIR *ptr_dir;

    ptr_dir = opendir(proc_dir);
    if (NULL == ptr_dir)
    {
        close_file_if_needed(write_to_file, stream);
        fprintf(stderr, "critical error: %s\n", strerror(errno));
        exit(errno);
    }

    while ((ptr_dirent = readdir(ptr_dir)) != NULL)
    {
        if (is_string_a_number(ptr_dirent->d_name))
        {
            fprintf(stream, "%s\n", ptr_dirent->d_name);
        }
    }

    close_file_if_needed(write_to_file, stream);
}

// option -u
void print_proc_name(char* pid, bool write_to_file, char* filename)
{
    FILE* stream = open_file_to_write_if_requested(write_to_file, filename);

    fprintf(stream, "-u %s\n", pid);
    
    close_file_if_needed(write_to_file, stream);
}

// option -n
void print_proc_pid(char* process_name, bool write_to_file, char* filename)
{
    FILE* stream = open_file_to_write_if_requested(write_to_file, filename);

    fprintf(stream, "-n %s\n", process_name);
    
    close_file_if_needed(write_to_file, stream);
}
#include "process_info.h"

const char *const PROC_PATH = "/proc";
const char *const FORWARD_SLASH_STR = "/";
const char *const CMDLINE_FILENAME = "cmdline";
const char *const ZOMBIE_PROCESS_STR = "[Z]";
const char FORWARD_SLASH_CHAR = '/';

FILE *open_file_to_write_if_requested(bool write_to_file, char *filename)
{
    const char *const mode = "w";
    FILE *stream = stdout;

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

void close_file_if_needed(bool write_to_file, FILE *stream)
{
    if (write_to_file && stream != NULL && stream != stdout)
    {
        fclose(stream);
    }
}

bool is_string_a_number(char *str)
{
    bool result = strlen(str) ? true : false;
    int i = 0;
    while (str[i])
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

char* get_last_element_from_path(char* path)
{
    for (int i = strlen(path) - 1; i >= 0; i--)
    {
        if (FORWARD_SLASH_CHAR == path[i])
        {
            strcpy(path, path + (i + 1));
            break;
        }
    }
    
    return path;
}

// option -a
void print_all_procs_info(bool write_to_file, char *filename)
{
    FILE *stream = open_file_to_write_if_requested(write_to_file, filename);

    struct dirent *ptr_proc_dirent = NULL;
    DIR *ptr_proc_dir = opendir(PROC_PATH);
    if (NULL == ptr_proc_dir)
    {
        close_file_if_needed(write_to_file, stream);
        fprintf(stderr, "critical error: %s\n", strerror(errno));
        exit(errno);
    }

    while ((ptr_proc_dirent = readdir(ptr_proc_dir)) != NULL)
    {
        if (is_string_a_number(ptr_proc_dirent->d_name))
        {
            char *proc_subpath = (char *)malloc(
                (strlen(PROC_PATH) +
                 strlen(FORWARD_SLASH_STR) +
                 strlen(ptr_proc_dirent->d_name) +
                 1) *
                sizeof(char));

            strcpy(proc_subpath, PROC_PATH);
            strcat(proc_subpath, FORWARD_SLASH_STR);
            strcat(proc_subpath, ptr_proc_dirent->d_name);

            struct dirent *ptr_proc_subdirent = NULL;
            DIR *ptr_proc_subdir = opendir(proc_subpath);
            if (NULL == ptr_proc_subdir)
            {
                close_file_if_needed(write_to_file, stream);
                fprintf(stderr, "critical error: %s\n", strerror(errno));
                exit(errno);
            }

            while ((ptr_proc_subdirent = readdir(ptr_proc_subdir)) != NULL)
            {
                if (!strcmp(ptr_proc_subdirent->d_name, CMDLINE_FILENAME))
                {
                    /* READING CMDLINE */
                    char *cmdline_path = (char *)malloc(
                        (strlen(proc_subpath) +
                         strlen(FORWARD_SLASH_STR) +
                         strlen(CMDLINE_FILENAME) +
                         1) *
                        sizeof(char));

                    strcpy(cmdline_path, proc_subpath);
                    strcat(cmdline_path, FORWARD_SLASH_STR);
                    strcat(cmdline_path, CMDLINE_FILENAME);

                    /* GETTING STRING LENGTH */
                    FILE *cmdline_stream = NULL;
                    int read_char = 'a';
                    int str_length = 0;
                    static const char *const mode = "r";

                    cmdline_stream = fopen(cmdline_path, mode);
                    if (NULL == cmdline_stream)
                    {
                        fprintf(stderr, "critical error: %s\n", strerror(errno));
                        exit(errno);
                    }

                    while ('\0' != (read_char = fgetc(cmdline_stream)) && ' ' != read_char && !feof(cmdline_stream))
                    {
                        str_length++;
                    }

                    fclose(cmdline_stream);

                    /* GETTING STRING */
                    if (str_length)
                    {
                        char *cmdline_content = (char *)malloc((str_length + 1) * sizeof(char));
                        
                        cmdline_stream = fopen(cmdline_path, mode);
                        if (NULL == cmdline_stream)
                        {
                            fprintf(stderr, "critical error: %s\n", strerror(errno));
                            exit(errno);
                        }

                        read_char = 'a';
                        int i = 0;
                        while ('\0' != (read_char = fgetc(cmdline_stream)) && ' ' != read_char && !feof(cmdline_stream))
                        {
                            cmdline_content[i] = read_char;
                            i++;
                        }
                        cmdline_content[i] = '\0';

                        /* PARSE STRING */
                        cmdline_content = get_last_element_from_path(cmdline_content);
                        fprintf(stream, "%s %s\n", cmdline_content, ptr_proc_dirent->d_name);

                        free(cmdline_content);
                    }
                    else 
                    {
                        fprintf(stream, "%s %s\n", ZOMBIE_PROCESS_STR, ptr_proc_dirent->d_name);
                    }

                    free(cmdline_path);
                    break;
                }
            }
            closedir(ptr_proc_subdir);
            free(proc_subpath);
        }
    }

    closedir(ptr_proc_dir);
    close_file_if_needed(write_to_file, stream);
}

// option -u
void print_proc_name(char *pid, bool write_to_file, char *filename)
{
    FILE *stream = open_file_to_write_if_requested(write_to_file, filename);

    fprintf(stream, "-u %s\n", pid);

    close_file_if_needed(write_to_file, stream);
}

// option -n
void print_proc_pid(char *process_name, bool write_to_file, char *filename)
{
    FILE *stream = open_file_to_write_if_requested(write_to_file, filename);

    fprintf(stream, "-n %s\n", process_name);

    close_file_if_needed(write_to_file, stream);
}
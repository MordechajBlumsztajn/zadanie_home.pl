#include "process_info.h"

const char *const PROC_PATH = "/proc";

/* TO DELETE ? */
const char *const FORWARD_SLASH_STR = "/";

/* TO DELETE */
const char *const CMDLINE_FILENAME = "cmdline";

const char *const PROC_NAME_FILENAME = "comm";

/* TO DELETE */
const char *const ZOMBIE_PROCESS_STR = "[Z]";

const char FORWARD_SLASH_CHAR = '/';

FILE *open_file_to_write_if_requested(char *filename)
{
    const char *const mode = "w";
    FILE *stream = stdout;

    if (filename != NULL)
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

void close_file_if_not_stdout(FILE *stream)
{
    if (stream != NULL && stream != stdout)
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

char *get_last_element_from_path(char *path)
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

char *create_path_from_2_strings(const char *const left, const char *const right)
{
    static const char *const FORWARD_SLASH_STR = "/";

    char *path = (char *)malloc(
        (strlen(left) +
         strlen(FORWARD_SLASH_STR) +
         strlen(right) +
         1) *
        sizeof(char));

    if (NULL == path)
    {
        fprintf(stderr, "critical error: %s\n", strerror(errno));
        exit(errno);
    }

    strcpy(path, left);
    strcat(path, FORWARD_SLASH_STR);
    strcat(path, right);

    return path;
}

DIR *opendir_and_verify(const char *const dirpath)
{
    DIR *ptr_proc_dir = opendir(dirpath);
    if (NULL == ptr_proc_dir)
    {
        fprintf(stderr, "critical error: %s\n", strerror(errno));
        exit(errno);
    }
    return ptr_proc_dir;
}

unsigned get_file_content_length(const char *const path)
{
    static const char *const read_mode = "r";
    int read_char = '\0';
    unsigned str_length = 0;
    
    FILE *stream = fopen(path, read_mode);
    if (NULL == stream)
    {
        fprintf(stderr, "critical error: %s\n", strerror(errno));
        exit(errno);
    }

    while ('\n' != (read_char = fgetc(stream)) && !feof(stream))
    {
        str_length++;
    }

    fclose(stream);
    return str_length;
}

char *get_file_content(const char *const path, unsigned length)
{
    static const char *const read_mode = "r";
    char *file_content = (char *)calloc((length + 1), sizeof(char));
    int read_char = '\0';

    FILE *stream = fopen(path, read_mode);
    if (NULL == stream)
    {
        fprintf(stderr, "critical error: %s\n", strerror(errno));
        exit(errno);
    }

    int i = 0;
    while ('\n' != (read_char = fgetc(stream)) && !feof(stream))
    {
        file_content[i] = read_char;
        i++;
    }

    return file_content;
}

// option -a
void print_all_procs_info(char *filename)
{
    FILE *stream = open_file_to_write_if_requested(filename);
    struct dirent *ptr_proc_dirent = NULL;
    DIR *ptr_proc_dir = opendir_and_verify(PROC_PATH);

    while ((ptr_proc_dirent = readdir(ptr_proc_dir)) != NULL)
    {
        if (is_string_a_number(ptr_proc_dirent->d_name))
        {
            char *proc_subpath = create_path_from_2_strings(PROC_PATH, ptr_proc_dirent->d_name);
            struct dirent *ptr_proc_subdirent = NULL;
            DIR *ptr_proc_subdir = opendir_and_verify(proc_subpath);

            while ((ptr_proc_subdirent = readdir(ptr_proc_subdir)) != NULL)
            {
                if (!strcmp(ptr_proc_subdirent->d_name, PROC_NAME_FILENAME))
                {
                    char *comm_path = create_path_from_2_strings(proc_subpath, PROC_NAME_FILENAME);
                    unsigned str_length = get_file_content_length(comm_path);
                    char *comm_content = get_file_content(comm_path, str_length);
                    fprintf(stream, "%s %s\n", comm_content, ptr_proc_dirent->d_name);

                    free(comm_content);
                    free(comm_path);
                    break;
                }
            }
            closedir(ptr_proc_subdir);
            free(proc_subpath);
        }
    }

    closedir(ptr_proc_dir);
    close_file_if_not_stdout(stream);
}

// option -u
void print_proc_name(char *pid, char *filename)
{
    FILE *stream = open_file_to_write_if_requested(filename);

    fprintf(stream, "-u %s\n", pid);

    close_file_if_not_stdout(stream);
}

// option -n
void print_proc_pid_from_name(char *process_name, char *filename)
{
    FILE *stream = open_file_to_write_if_requested(filename);
    struct dirent *ptr_proc_dirent = NULL;
    DIR *ptr_proc_dir = opendir_and_verify(PROC_PATH);
    bool proc_found = false;
    
    while ((ptr_proc_dirent = readdir(ptr_proc_dir)) != NULL)
    {
        if (is_string_a_number(ptr_proc_dirent->d_name))
        {
            char *proc_subpath = create_path_from_2_strings(PROC_PATH, ptr_proc_dirent->d_name);
            struct dirent *ptr_proc_subdirent = NULL;
            DIR *ptr_proc_subdir = opendir_and_verify(proc_subpath);
            
            while ((ptr_proc_subdirent = readdir(ptr_proc_subdir)) != NULL)
            {
                if (!strcmp(ptr_proc_subdirent->d_name, PROC_NAME_FILENAME))
                {
                    char *comm_path = create_path_from_2_strings(proc_subpath, PROC_NAME_FILENAME);
                    unsigned str_length = get_file_content_length(comm_path);
                    char *comm_content = get_file_content(comm_path, str_length);

                    if (!strcmp(comm_content, process_name))
                    {
                        proc_found = true;
                        fprintf(stream, "%s ", ptr_proc_dirent->d_name);
                    }
                    
                    free(comm_content);
                    free(comm_path);
                    break;
                }
            }
            closedir(ptr_proc_subdir);
            free(proc_subpath);
        }
    }

    if (proc_found)
    {
        fprintf(stream, "\n");
    }
    else
    {
        fprintf(stream, "not found: No process with given name found: %s.\n", process_name);
    }

    closedir(ptr_proc_dir);
    close_file_if_not_stdout(stream);
}
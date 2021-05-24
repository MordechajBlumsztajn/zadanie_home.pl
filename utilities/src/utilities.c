#include "utilities.h"

const char *const PROC_PATH = "/proc";
const char *const PROC_NAME_FILENAME = "comm";
const char *const HELP_STR = 
"usage: %s: { -a | -u <pid> | -n <name> } [ -f <file> ]\n"
"description:\n"
"   -a\n"
"       print pids and names of all running processes\n"
"   -u <pid>\n"
"       print name of process with given <pid>\n"
"   -n <name>\n"
"       print pid of process with given <name>\n"
"   -f <file>\n"
"       write output to <file> instead of stdout\n";

FC generate_empty_flags_container()
{
    FC flags;
    flags.opts = NO_OPT_FLAG;
    flags.errors = NO_ERROR;
    return flags;
}

int set_flag(int flag, int mask)
{
    return flag | mask;
}

int unset_flag(int flag, int mask)
{
    return flag & ~mask;
}

bool is_flag_set(int flag, int mask)
{
    return (flag & mask) > 0;
}

bool is_flag_not_set(int flag, int mask)
{
    return (flag & mask) == 0;
}

bool is_any_flag_set(int flag)
{
    return flag > 0;
}

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
    static const char FORWARD_SLASH_CHAR = '/';

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

void print_help(const char *prog_name)
{
    fprintf(stdout, HELP_STR, prog_name);
}
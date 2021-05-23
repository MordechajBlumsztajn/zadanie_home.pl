#ifndef PID_DISPLAYER_UTILITIES_H
#define PID_DISPLAYER_UTILITIES_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>

extern const char *const PROC_PATH;
extern const char *const PROC_NAME_FILENAME;

enum OPTS_FLAG
{
    NO_OPT_FLAG     = 0x0,

    OPT_a_FLAG      = 0x1, // mandatory and exclusive
    OPT_u_FLAG      = 0x2, // mandatory and exclusive
    OPT_n_FLAG      = 0x4, // mandatory and exclusive

    OPT_f_FLAG      = 0x8 // optional and inclusive
};

enum OPTS_WITH_ARGS_INDEX_ORDER
{
    OPT_u_INDEX = 0,
    OPT_n_INDEX = 1,
    OPT_f_INDEX = 2
};

enum OPTS_ERROR_FLAG
{
    NO_ERROR                = 0x0,
    UNKNOWN_OPTION_ERROR    = 0x1,
    ARG_REQUIRED_ERROR      = 0x2,
    MANDATORY_OPT_ERROR     = 0x4,
    EXCLUSIVE_OPTS_ERROR    = 0x8,
    NON_OPT_ARG_ERROR       = 0x10
};

struct flags_container
{
    int opts;
    int errors;
};
typedef struct flags_container FC;

FC generate_empty_flags_container();
int set_flag(int flag, int mask);
int unset_flag(int flag, int mask);
bool is_flag_set(int flag, int mask);
bool is_flag_not_set(int flag, int mask);
bool is_any_flag_set(int flag);

FILE* open_file_to_write_if_requested(char* filename);
void close_file_if_not_stdout(FILE* stream);
bool is_string_a_number(char *str);
char *get_last_element_from_path(char *path);
char *create_path_from_2_strings(const char *const left, const char *const right);
DIR *opendir_and_verify(const char *const dirpath);
unsigned get_file_content_length(const char *const path);
char *get_file_content(const char *const path, unsigned length);

#endif

#ifndef PID_DISPLAYER_UTILITIES_H
#define PID_DISPLAYER_UTILITIES_H

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

enum MAIN_FUNC_RESULT 
{
    SUCCESS_RESULT = 0,
    FAILURE_RESULT = 1
};

struct flags_container
{
    int opt_flags;
    int errors_flags;
};
typedef struct flags_container FC;

FC generate_empty_flags_container();

#endif

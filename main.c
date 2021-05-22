#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

enum OPTS_FLAG
{
    NO_OPT_FLAG     = 0x0,

    OPT_a_FLAG      = 0x1, // mandatory and exclusive
    OPT_u_FLAG      = 0x2, // mandatory and exclusive
    OPT_n_FLAG      = 0x4, // mandatory and exclusive

    OPT_f_FLAG      = 0x8 // optional
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

FC generate_empty_flags_container()
{
    FC flags;
    flags.opt_flags = NO_OPT_FLAG;
    flags.errors_flags = NO_ERROR;
}

void copy_option_argument(char** destination, enum OPTS_WITH_ARGS_INDEX_ORDER index, char* source)
{
    destination[index] = (char*) malloc((strlen(source) + 1) * sizeof(char));
    if (NULL == destination[index])
    {
        exit(ENOMEM);
    }
    strcpy(destination[index], source);
}

FC parse_input(int argc, char* argv[], char* optsargs[], FC flags)
{
    const char* const OPTS_STRING = ":au:n:f:";

    int opt = 0;
    while ((opt = getopt(argc, argv, OPTS_STRING)) != -1)
    {
        switch (opt)
        {
        case 'a':
            flags.opt_flags |= OPT_a_FLAG;
            break;
        case 'u':
            copy_option_argument(optsargs, OPT_u_INDEX, optarg);
            flags.opt_flags |= OPT_u_FLAG;
            break;
        case 'n':
            copy_option_argument(optsargs, OPT_n_INDEX, optarg);
            flags.opt_flags |= OPT_n_FLAG;
            break;
        case 'f':
            copy_option_argument(optsargs, OPT_f_INDEX, optarg);
            flags.opt_flags |= OPT_f_FLAG;
            break;
        case '?':
            flags.errors_flags |= UNKNOWN_OPTION_ERROR;
            fprintf(stderr, "error: Unknown option: %c.\n", optopt);
            break;
        case ':':
            flags.errors_flags |= ARG_REQUIRED_ERROR;
            fprintf(stderr, "error: Option %c requires an argument.\n", optopt);

            switch (optopt)
            {
            case 'u':
                flags.opt_flags |= OPT_u_FLAG;
                break;
            case 'n':
                flags.opt_flags |= OPT_n_FLAG;
                break;
            }
            
            break;
        }
    }
    return flags;
}

FC check_for_mandatory_option(FC flags)
{
    if (!(flags.opt_flags & (OPT_a_FLAG | OPT_u_FLAG | OPT_n_FLAG)))
    {
        fprintf(stderr, "error: One of these options needs to be chosen: -a, -u, -n.\n");
        flags.errors_flags |= MANDATORY_OPT_ERROR;
    }
    return flags;
}

FC check_for_options_exclusivity(FC flags)
{
    const int MAX_EXCLUSIVE_OPTS_COUNT = 1;

    if ((((flags.opt_flags & OPT_a_FLAG) > 0) + ((flags.opt_flags & OPT_u_FLAG) > 0) + 
            ((flags.opt_flags & OPT_n_FLAG) > 0)) > MAX_EXCLUSIVE_OPTS_COUNT)
    {
        fprintf(stderr, "error: Only one of these options can be chosen: -a, -u, -n.\n");
        flags.errors_flags |= EXCLUSIVE_OPTS_ERROR;
    }
    return flags;
}

FC check_for_non_optional_arguments(int argc, char* argv[], FC flags)
{
    if (optind < argc)
    {
        fprintf(stderr, "error: Program does not accept non-optional arguments:");
    
        while (optind < argc)
        {
            printf(" \"%s\"", argv[optind++]);
        }
        printf(".\n");
        flags.errors_flags |= NON_OPT_ARG_ERROR;
    }

    return flags;
}

bool error_occurred(FC flags)
{
    return flags.errors_flags > 0;
}

char** allocate_memory_for_option_arguments(int args_count)
{
    char** optargs = (char**) malloc(args_count * sizeof(char*));
    if (NULL == optargs)
    {
        exit(ENOMEM);
    }

    for (size_t i = 0; i < args_count; i++)
    {
        optargs[i] = NULL;
    }

    return optargs;
}

void deallocate_option_arguments_memory(char** optargs, int args_count)
{
    for (size_t i = 0; i < args_count; i++)
    {
        free(optargs[i]);
    }
    
    free(optargs);
}

void execute_chosen_command(FC flags, char* opts_args[])
{
    fprintf(stdout, "ARGUMENTS: ");
        if (flags.opt_flags & OPT_u_FLAG)
        {
            printf("-u %s ", opts_args[OPT_u_INDEX]);
        }

        if (flags.opt_flags & OPT_n_FLAG)
        {
            printf("-n %s ", opts_args[OPT_n_INDEX]);
        }

        if (flags.opt_flags & OPT_f_FLAG)
        {
            printf("-f %s ", opts_args[OPT_f_INDEX]);
        }

        printf("\n");
}

int main(int argc, char *argv[])
{
    int result = SUCCESS_RESULT;

    const int OPTS_WITH_ARGS_COUNT = 3;
    char** optargs = allocate_memory_for_option_arguments(OPTS_WITH_ARGS_COUNT);

    FC flags = generate_empty_flags_container();
    flags = parse_input(argc, argv, optargs, flags);
    flags = check_for_mandatory_option(flags);
    flags = check_for_options_exclusivity(flags);
    flags = check_for_non_optional_arguments(argc, argv, flags);

    if (error_occurred(flags))
    {
        result = FAILURE_RESULT;
    }
    else
    {
        execute_chosen_command(flags, optargs);
    }
    deallocate_option_arguments_memory(optargs, OPTS_WITH_ARGS_COUNT);

    return result;
}

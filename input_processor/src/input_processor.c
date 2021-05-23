#include "input_processor.h"

void copy_option_argument(char** destination, enum OPTS_WITH_ARGS_INDEX_ORDER index, char* source)
{
    destination[index] = (char*) malloc((strlen(source) + 1) * sizeof(char));
    if (NULL == destination[index])
    {
        fprintf(stderr, "critical error: %s\n", strerror(errno));
        exit(errno);
    }
    strcpy(destination[index], source);
}

FC parse_input(int argc, char* argv[], char* optargs[], FC flags)
{
    const char* const OPTS_STRING = ":au:n:f:";

    int opt = 0;
    while ((opt = getopt(argc, argv, OPTS_STRING)) != -1)
    {
        switch (opt)
        {
        case 'a':
            flags.opts = set_flag(flags.opts, OPT_a_FLAG);
            break;
        case 'u':
            copy_option_argument(optargs, OPT_u_INDEX, optarg);
            flags.opts = set_flag(flags.opts, OPT_u_FLAG);
            break;
        case 'n':
            copy_option_argument(optargs, OPT_n_INDEX, optarg);
            flags.opts = set_flag(flags.opts, OPT_n_FLAG);
            break;
        case 'f':
            copy_option_argument(optargs, OPT_f_INDEX, optarg);
            flags.opts = set_flag(flags.opts, OPT_f_FLAG);
            break;
        case '?':
            flags.errors = set_flag(flags.errors, UNKNOWN_OPTION_ERROR);
            fprintf(stderr, "error: Unknown option: %c.\n", optopt);
            break;
        case ':':
            flags.errors = set_flag(flags.errors, ARG_REQUIRED_ERROR);
            fprintf(stderr, "error: Option %c requires an argument.\n", optopt);

            switch (optopt)
            {
            case 'u':
                flags.opts = set_flag(flags.opts, OPT_u_FLAG);
                break;
            case 'n':
                flags.opts = set_flag(flags.opts, OPT_n_FLAG);
                break;
            }
            
            break;
        }
    }
    return flags;
}

FC check_for_mandatory_option(FC flags)
{
    if (is_flag_not_set(flags.opts, OPT_a_FLAG | OPT_u_FLAG | OPT_n_FLAG))
    {
        flags.errors = set_flag(flags.errors, MANDATORY_OPT_ERROR);
        fprintf(stderr, "error: One of these options needs to be chosen: -a, -u, -n.\n");
    }
    return flags;
}

FC check_for_option_exclusivity(FC flags)
{
    const int MAX_EXCLUSIVE_OPTS_COUNT = 1;

    if (is_flag_set(flags.opts, OPT_a_FLAG) + 
        is_flag_set(flags.opts, OPT_u_FLAG) +
        is_flag_set(flags.opts, OPT_n_FLAG) > 
        MAX_EXCLUSIVE_OPTS_COUNT)
    {
        flags.errors = set_flag(flags.errors, EXCLUSIVE_OPTS_ERROR);
        fprintf(stderr, "error: Only one of these options can be chosen: -a, -u, -n.\n");
    }
    return flags;
}

FC check_for_non_optional_arguments(int argc, char* argv[], FC flags)
{
    if (optind < argc)
    {
        flags.errors = set_flag(flags.errors, NON_OPT_ARG_ERROR);
        fprintf(stderr, "error: Program does not accept non-optional arguments:");
    
        while (optind < argc)
        {
            printf(" \"%s\"", argv[optind++]);
        }
        printf(".\n");
    }

    return flags;
}

bool error_occurred(FC flags)
{
    return is_any_flag_set(flags.errors);
}

char** allocate_memory_for_option_arguments(unsigned args_count)
{
    char** optargs = (char**) calloc(args_count, sizeof(char*));
    if (NULL == optargs)
    {
        fprintf(stderr, "critical error: %s\n", strerror(errno));
        exit(errno);
    }

    return optargs;
}

void deallocate_option_arguments_memory(char** optargs, unsigned args_count)
{
    for (unsigned i = 0; i < args_count; i++)
    {
        free(optargs[i]);
    }
    
    free(optargs);
}
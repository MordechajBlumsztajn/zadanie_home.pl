#include <stdio.h>

#include "utilities.h"
#include "input_processor.h"


void execute_chosen_command(FC flags, char* opts_args[]);


int main(int argc, char *argv[])
{
    int result = SUCCESS_RESULT;
    const unsigned OPTS_WITH_ARGS_COUNT = 3;
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
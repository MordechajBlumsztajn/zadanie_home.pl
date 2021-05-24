#include <stdio.h>

#include "utilities.h"
#include "input_processor.h"
#include "process_info.h"

void execute_chosen_command(FC flags, char *opts_args[]);

int main(int argc, char *argv[])
{
    int result = EXIT_SUCCESS;
    const unsigned OPTS_WITH_ARGS_COUNT = 3;
    char **optargs = allocate_memory_for_option_arguments(OPTS_WITH_ARGS_COUNT);
    FC flags = generate_empty_flags_container();

    flags = parse_input(argc, argv, optargs, flags);
    flags = check_for_mandatory_option(flags);
    flags = check_for_option_exclusivity(flags);
    flags = check_for_non_optional_arguments(argc, argv, flags);
    flags = check_for_numeric_arg(optargs, flags);

    if (error_occurred(flags))
    {
        result = EXIT_FAILURE;
        print_help(argv[0]);
    }
    else
    {
        execute_chosen_command(flags, optargs);
    }
    deallocate_option_arguments_memory(optargs, OPTS_WITH_ARGS_COUNT);
    
    return result;
}

void execute_chosen_command(FC flags, char *optargs[])
{
    char* filename = is_flag_set(flags.opts, OPT_f_FLAG)? optargs[OPT_f_INDEX] : NULL;

    switch(unset_flag(flags.opts, OPT_f_FLAG))
    {
        case OPT_a_FLAG:
            print_all_procs_info(filename);
            break;
        case OPT_u_FLAG:
            print_proc_name_from_pid(optargs[OPT_u_INDEX], filename);
            break;
        case OPT_n_FLAG:
            print_proc_pid_from_name(optargs[OPT_n_INDEX], filename);
            break;
    }
}
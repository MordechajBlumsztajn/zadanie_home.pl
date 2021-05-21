#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

const int MIN_ARGUMENT_COUNT = 2;
const int MAX_EXCLUSIVE_OPTIONS = 1;

enum OPT_FLAG { 
    FLAG_a = 1, 
    FLAG_u = 2, 
    FLAG_n = 4, 
    FLAG_f = 8 
    };

struct dupa {

};

int main(int argc, char *argv[])
{
    bool failure_occurred = false;

    bool chosen_opt_a = false;
    bool chosen_option_u = false;
    bool chosen_option_n = false;

    int exclusive_option_counter = 0;

    int opt = 0;
    while ((opt = getopt(argc, argv, ":au:n:f:")) != -1)
    {
        switch (opt)
        {
        case 'a':
            exclusive_option_counter++;
            chosen_opt_a = true;
            break;
        case 'u':
            exclusive_option_counter++;
            chosen_option_u = true;
            break;
        case 'n':
            exclusive_option_counter++;
            chosen_option_n = true;
            break;
        case 'f':
            break;
        case '?':
            fprintf(stderr, "error: Unknown option: %c.\n", optopt);
            failure_occurred = true;
            break;
        case ':':
            fprintf(stderr, "error: Option %c requires an argument.\n", optopt);
            failure_occurred = true;
            break;
        }
    }

    if (0 == exclusive_option_counter)
    {
        fprintf(stderr, "error: One (and only one) of these options needs to be chosen: -a, -u, -n.\n");
        failure_occurred = true;
    }
    else if (MAX_EXCLUSIVE_OPTIONS < exclusive_option_counter)
    {
        fprintf(stderr, "error: Only one of these options can be chosen: -a, -u, -n.\n");
        failure_occurred = true;
    }

    if (optind < argc)
    {
        fprintf(stderr, "error: Program does not accept non-optional arguments: ");
        failure_occurred = true;

        while (optind < argc)
        {
            printf(" %s", argv[optind++]);
        }
        printf("\n");
    }

    if (true == failure_occurred)
    {
        fprintf(stderr, "Terminating execution...\n");
        return 1;
    }

    if (true == chosen_opt_a)
    {

    }
    else if (true == chosen_option_n)
    {

    }
    else if (true == chosen_option_u)
    {
        
    }

    return 0;
}

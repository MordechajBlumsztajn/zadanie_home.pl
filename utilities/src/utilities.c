#include "utilities.h"

FC generate_empty_flags_container()
{
    FC flags;
    flags.opt_flags = NO_OPT_FLAG;
    flags.errors_flags = NO_ERROR;
    return flags;
}
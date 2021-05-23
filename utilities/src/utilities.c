#include "utilities.h"

FC generate_empty_flags_container()
{
    FC flags;
    flags.opt_flags = NO_OPT_FLAG;
    flags.errors_flags = NO_ERROR;
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
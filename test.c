#include "cbase/cbase.h"

int
main (int argc, char **argv)
{
    error_handler = &print_to_stderr;
    return 0;
}

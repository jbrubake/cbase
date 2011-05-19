#!/bin/sh

#
# This script is called by the toplevel Makefile and is
# responsible for creating the *.d files in each subdirectory.
# These files include all dependency information for the build
# system (assuming your toplevel Makefile and modules.mk files
# are setup correctly)
#
# There should generally be no reason to call this file directly
#

DIR="$1"

shift 1

case "$DIR" in
    "" | ".")
        gcc  -MM -MG "$@" | sed -e 's@^\(.*\)\.o:@\1.d \1.o:@'
        ;;

    *)
        gcc -MM -MG "$@" | sed -e "s@^\(.*\)\.o:@$DIR/\1.d $DIR/\1.o:@"
        ;;
esac

#!/bin/bash

# Command line options:
#
# -n, --project-name            PROJECT
# -r, --release                 1.0.0
# -a, --author                  $USER, comma-separated list
# -e, --email                   $USER@localhost, comma-separated list
# -p, --path-to-cbase           /usr/local/share/cbase
# -d, --directory               .
# -s, --version-control-system  NONE
# -w, --build-for-windows       FALSE
# -h, --help
# -V, --version
# -v, --verbose

# Sensible defaults
PROJECT_NAME='%PROJECT%'
RELEASE='%VERSION%'
AUTHORS="$USER"
EMAILS="$AUTHORS@localhost"
CBASE_DIR="/usr/local/share/cbase"
PROJ_DIR=
VCS='NONE'
OSTYPE='nix'
verbose='no'

# XXX: I have added options above that aren't covered below
optstring=':n:r:a:e:f:p:d:s:chVv'
VERSION='1.0.0'

#
# Process options
#
while getopts $optstring option $@; do
    case $option in
        n)
        PROJECT_NAME="$OPTARG"
        ;;
        r)
        RELEASE="$OPTARG"
        ;;
        a)
        AUTHORS="\n$OPTARG"
        ;;
        p)
        # Could probably have some more robust checking
        if [ -d "$OPTARG" ]; then
            CBASE_DIR="$OPTARG"
        else
            echo "$OPTARG is not a directory";
        fi
        ;;
        d)
        # Could probably have some more robust checking
        if [ -d "$OPTARG" ]; then
            PROJ_DIR="$OPTARG/"
        else
            echo "$OPTARG is not a directory";
        fi
        ;;
        s)
        case $OPTARG in
            git*)
            VCS='git'
            ;;
            cvs*)
            VCS='cvs'
            ;;
            subversion*)
            VCS='subversion'
            ;;
            *)
            echo "Unkown version control system $OPTARG"
            ;;
        esac
        ;;
        c)
        OSTYPE='cygwin'
        ;;
        h)
        cat << END_HELP
Usage: cbase [OPTION]
Set up a base C project directory in the current directory

-n, --project-name            Project name. Default is PROJECT
-r, --release                 Project release number. Default is 1.0.0
-a, --author                  Author line for AUTHORS file. You can
                                  have multiple -a's to add multiple
                                  authors. Default is $USER
-d, --path-to-cbase           Path to the base project. Default is 
                                  /usr/local/share/cbase
-s, --version-control-system  Version control system to initialize.
                                  Excepts: git, cvs and subversion.
                                  Default is to not use one
-c, --build-for-cygwin        Set the project up to be built under
                                  Cygwin. Default is no
-v, --verbose                 Echo all commands
-h, --help
-V, --version
END_HELP
        ;;
        V)
        cat << END_VERSION
cbase $VERSION

Copyright (C) 2010 Jeremy Brubaker
This is free software; see the GNU General Public License for copying
conditions. There is NO warranty; not even for MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.

END_VERSION
        ;;
        v)
        verbose='yes' 
        ;;
        :)
        echo "Option -$OPTARG requires argument"
        ;;
        *)
        echo "Unkown option -$OPTARG"
        ;;
    esac;
done

# chdir to base directory if requested
if [ "$PROJ_DIR" ]; then
    cd "$PROJ_DIR"
fi

# Turn on verbose output if requested
if [ $verbose == 'yes' ]; then
    set -x
fi

# Create base directory tree
install -d "$PROJECT_NAME-$RELEASE"
cd "$PROJECT_NAME-$RELEASE"

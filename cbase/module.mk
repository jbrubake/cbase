SRCFILES += cbase/error.c \
	    cbase/except.c \
	    cbase/logfile.c \
	    cbase/util.c \
	    cbase/xmalloc.c \
	    cbase/bstrlib.c \
	    cbase/xtime.c

HDRFILES += $(SRCFILES:.c=.h) \
	    cbase/cbase.h \
	    cbase/private.h

AUXFILES += cbase/AUTHORS \
	    cbase/module.mk

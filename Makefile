#
# makefile for filelist converter; PCBoard -> DayDream (longfilenames).
#

CC	= gcc
LIBDIR  = 
MAINDIR = 

CFLAGS  =

LIBS	= 

all:		pcbf2ddf

pcbf2ddf:       pcbf2ddf.c
	        $(CC) -o $@ $<


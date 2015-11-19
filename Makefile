########################################################################
# COSC1076 - Advanced Programming Techniques
# Semester 2 2014 Assignment #2
# Full Name        : EDIT HERE
# Student Number   : EDIT HERE
# Course Code      : EDIT HERE
# Program Code     : EDIT HERE
# Start up code provided by Paul Miller
########################################################################


########################################################################
# Move this target to the end of the Makefile to zip up your code 
# when submitting. Do not submit your .dat files, or directories. 
# We only want the files that are part of your implementation.
########################################################################
SOURCES=ppd_main.c ppd_menu.c ppd_options.c ppd_utility.c ppd_stock.c ppd_coin.c
HEADERS=ppd_main.h ppd_menu.h ppd_options.h    ppd_utility.h ppd_stock.h ppd_coin.h
README=ppd_readme
MAKEFILE=Makefile

CC = gcc

CFLAGS = -ansi -Wall -pedantic
CDEBUG= -g
OBJS= $(SOURCES:.c=.o)

EXE= ppd

USER= s3466760

all:		$(EXE)

$(EXE):	$(OBJS)
		  $(CC) $(CFAGS) $(OBJS) -o $@

%.o:	%.c
		  $(CC) $(CFLAGS) $< -c -o $@  


debug:	$(SOURCES)
		  $(CC) $(CFLAGS) $(CDEBUG) $(SOURCES) -o $(EXE)

.PHONY: clean archive 

clean:
		  rm -rf *.o *.out $(EXE) 





archive:
	       zip $(USER)-a2 $(SOURCES) $(HEADERS) $(README) $(MAKEFILE)

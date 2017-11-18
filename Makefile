# Makefile for the smash program
CC = g++
CFLAGS = -g -Wall
CCLINK = $(CC)
OBJS = smash.o commands.o signals.o jobs.o history.o
RM = rm -f
# Creating the  executable
smash: $(OBJS)
	$(CCLINK) -o smash $(OBJS)
# Creating the object files
commands.o: commands.c commands.h
smash.o: smash.c commands.h
signals.o: signals.c signals.h
jobs.o: jobs.cpp jobs.h
history.o: history.cpp history.h
# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *~ "#"* core.*

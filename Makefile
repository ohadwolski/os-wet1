# Makefile for the smash program
all: smash
CC = g++
CFLAGS = -g -Wall
CCLINK = $(CC)
OBJS = smash.o commands.o signals.o jobs.o history.o
RM = rm -f
# Creating the  executable
smash: $(OBJS)
	$(CCLINK) -o smash $(OBJS)
# Creating the object files
commands.o: commands.cpp commands.h signals.h history.h jobs.h
smash.o: smash.cpp commands.h signals.h history.h jobs.h
signals.o: signals.cpp signals.h commands.h history.h jobs.h
jobs.o: jobs.cpp jobs.h commands.h signals.h history.h
history.o: history.cpp history.h commands.h signals.h jobs.h
# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *~ "#"* core.*

#ifndef _COMMANDS_H
#define _COMMANDS_H
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <list>
#include <iostream>
#include <stdbool.h>
#include "history.h"
#include "jobs.h"

extern jobs_list* jobs;
extern history_list* history;

#define MAX_LINE_SIZE 80
#define MAX_ARG 20
//typedef enum { FALSE , TRUE } bool;
int ExeComp(char* lineSize);
int BgCmd(char* lineSize); //, void* jobs);
int ExeCmd(char* lineSize, char* cmdString);  //void* jobs,
void ExeExternal(char *args[MAX_ARG], char* cmdString);

void move_fg_to_bg();
void new_fg(int pID, char* name);
void remove_fg();

//extern history_list* history;
//extern jobs_list* jobs;

extern int running_in_fg;
extern char* running_in_fg_name;
#endif

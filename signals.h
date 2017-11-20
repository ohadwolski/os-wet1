#ifndef _SIGS_H
#define _SIGS_H
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <vector>
#include <iostream>
//#include "history.h"
//#include "jobs.h"
//#include "commands.h"


void ctrlC_Hndlr(int sig);
void ctrlZ_Hndlr(int sig);

extern int running_in_fg;
extern char* running_in_fg_name;

#endif

/*	smash.c
main file. This file contains the main function of smash
*******************************************************************/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "commands.h"
#include "signals.h"
#include "history.h"
#include "jobs.h"
#include <iostream>
#define MAX_LINE_SIZE 80
#define MAXARGS 20
using namespace std;


char* L_Fg_Cmd;
//void* jobs = NULL; //This represents the list of jobs. Please change to a preferred type (e.g array of char*)
char lineSize[MAX_LINE_SIZE];
history_list* history = new history_list();
jobs_list* jobs = new jobs_list();
int running_in_fg = 0;
char* running_in_fg_name = NULL;

void move_fg_to_bg()
{
	job* job_c = new job(jobs->getNextJobNum(), running_in_fg, running_in_fg_name);
	job_c->changeStopped();
	jobs->addJob(job_c);
	delete job_c;

	//////// changing fg status
	running_in_fg = 0;
	free(running_in_fg_name);
	running_in_fg_name = NULL;
	////////
}

void new_fg(int pID, char* name)
{
	////////////////////// changing fg status
	running_in_fg = pID;
	if (running_in_fg_name)
		free(running_in_fg_name);
	running_in_fg_name = (char*)malloc((strlen(name)+1)*sizeof(char));
	if (!running_in_fg_name)
	{
		cout << "malloc failed!" << endl;
		return;
	}
	strcpy(running_in_fg_name, name);
	///////////////////////
}

void remove_fg()
{
	running_in_fg = 0;
	free(running_in_fg_name);
	running_in_fg_name = NULL;
}

//**************************************************************************************
// function name: main
// Description: main function of smash. get command from user and calls command functions
//**************************************************************************************
int main(int argc, char *argv[])
{
    char cmdString[MAX_LINE_SIZE];


	//signal declaretions
	//NOTE: the signal handlers and the function/s that sets the handler should be found in siganls.c
	struct sigaction ctrlC_act, ctrlZ_act;

	/************************************/
	//set your signal handlers here
	//intializing ctrlC_act
	sigfillset(&ctrlC_act.sa_mask);
	ctrlC_act.sa_flags= SA_RESTART;
	ctrlC_act.sa_handler = &ctrlC_Hndlr;

	//intializing ctrlZ_act
	sigfillset(&ctrlZ_act.sa_mask);
	ctrlZ_act.sa_flags = SA_RESTART;
	ctrlZ_act.sa_handler = &ctrlZ_Hndlr;


	sigaction(SIGINT,&ctrlC_act,NULL);
	sigaction(SIGTSTP,&ctrlZ_act,NULL);
	/************************************/
	// Init globals



	L_Fg_Cmd =(char*)malloc(sizeof(char)*(MAX_LINE_SIZE+1));
	if (L_Fg_Cmd == NULL)
			exit (-1);
	L_Fg_Cmd[0] = '\0';

    	while (1)
    	{
	 	printf("smash > ");
		fgets(lineSize, MAX_LINE_SIZE, stdin);
		strcpy(cmdString, lineSize);
		cmdString[strlen(lineSize)-1]='\0';

          // adding history record
    history->add(cmdString);

					// perform a complicated Command
		if(!ExeComp(lineSize)) continue;
					// background command
	 	if(!BgCmd(lineSize)) continue;
					// built in commands
		ExeCmd(lineSize, cmdString);

		/* initialize for next line read*/
		lineSize[0]='\0';
		cmdString[0]='\0';
	}
    return 0;
}

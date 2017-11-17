//		commands.c
//********************************************
#include "commands.h"
#include <unistd.h>
using namespace std;
//********************************************
// globals

static char prevPath[MAX_LINE_SIZE] = NULL; // used inorder to maintain previous path
//********************************************
// function name: ExeCmd
// Description: interperts and executes built-in commands
// Parameters: pointer to jobs, command string
// Returns: 0 - success,1 - failure
//**************************************************************************************
int ExeCmd(void* jobs, char* lineSize, char* cmdString)
{
	char* cmd;
	char* args[MAX_ARG];
	char pwd[MAX_LINE_SIZE];
	char* delimiters = " \t\n";
	int i = 0, num_arg = 0;
	bool illegal_cmd = FALSE; // illegal command
    	cmd = strtok(lineSize, delimiters);
	if (cmd == NULL)
		return 0;
   	args[0] = cmd;
	for (i=1; i<MAX_ARG; i++)
	{
		args[i] = strtok(NULL, delimiters);
		if (args[i] != NULL)
			num_arg++;

	}
/*************************************************/
// Built in Commands PLEASE NOTE NOT ALL REQUIRED
// ARE IN THIS CHAIN OF IF COMMANDS. PLEASE ADD
// MORE IF STATEMENTS AS REQUIRED
/*************************************************/
	if (!strcmp(cmd, "cd") )
	{
		if (num_arg !=1)
		{
			illegal_cmd = TRUE;
		} else
		{
			getcwd(pwd, MAX_LINE_SIZE) 				// getting current directory
			if (strcmp(args[1], "-")					// change to previous dir
			{
				if (prevPath == NULL) 					// We havnt changed a dir yet Is this behav correct?
				{
					strcpy(prevPath, pwd);
					cout << prevPath << endl;
				} else
				{
					if (chdir(prevPath) == -1)	 // Can't find previous path
					{
						cout << "smash error: > " << prevPath << " - path not found" << endl;
						return 1;
					} else											// change to last dir and change prevPath
					{
						cout << prevPath << endl;
						strcpy(prevPath, pwd);
					}
				}
			} else													// change to new dir
			{
				if (chdir(arg[1]) == -1)
				{
					cout << "smash error: > " << arg[1] << " - path not found" << endl;
					return 1;
				} else
				{
					strcpy(prevPath, pwd);
				}
			}
		}
	}

	/*************************************************/
	else if (!strcmp(cmd, "pwd"))
	{
		if (num_arg != 0)
		{
			illegal_cmd = TRUE;
		} else
		{
			cout << getpwd(pwd, MAX_LINE_SIZE) << endl;
		}
	}
	/*************************************************/
	else if (!strcmp(cmd, "history"))
	{

	}

	/*************************************************/
	else if (!strcmp(cmd, "kill"))
	{

	}
	/*************************************************/
	else if (!strcmp(cmd, "mv"))
	{

	}
	/*************************************************/

	else if (!strcmp(cmd, "jobs"))
	{

	}
	/*************************************************/
	else if (!strcmp(cmd, "showpid"))
	{

	}
	/*************************************************/
	else if (!strcmp(cmd, "fg"))
	{

	}
	/*************************************************/
	else if (!strcmp(cmd, "bg"))
	{

	}
	/*************************************************/
	else if (!strcmp(cmd, "quit"))
	{

	}
	/*************************************************/
	else // external command
	{
 		ExeExternal(args, cmdString);
	 	return 0;
	}
	if (illegal_cmd == TRUE)
	{
		printf("smash error: > \"%s\"\n", cmdString);
		return 1;
	}
    return 0;
}
//**************************************************************************************
// function name: ExeExternal
// Description: executes external command
// Parameters: external command arguments, external command string
// Returns: void
//**************************************************************************************
void ExeExternal(char *args[MAX_ARG], char* cmdString)
{
	int pID;
    	switch(pID = fork())
	{
    		case -1:
					// Add your code here (error)

					/*
					your code
					*/
        	case 0 :
                	// Child Process
               		setpgrp();

			        // Add your code here (execute an external command)

					/*
					your code
					*/

			default:
                	// Add your code here

					/*
					your code
					*/
	}
}
//**************************************************************************************
// function name: ExeComp
// Description: executes complicated command
// Parameters: command string
// Returns: 0- if complicated -1- if not
//**************************************************************************************
int ExeComp(char* lineSize)
{
	char ExtCmd[MAX_LINE_SIZE+2];
	char *args[MAX_ARG];
    if ((strstr(lineSize, "|")) || (strstr(lineSize, "<")) || (strstr(lineSize, ">")) || (strstr(lineSize, "*")) || (strstr(lineSize, "?")) || (strstr(lineSize, ">>")) || (strstr(lineSize, "|&")))
    {
		// Add your code here (execute a complicated command)

		/*
		your code
		*/
	}
	return -1;
}
//**************************************************************************************
// function name: BgCmd
// Description: if command is in background, insert the command to jobs
// Parameters: command string, pointer to jobs
// Returns: 0- BG command -1- if not
//**************************************************************************************
int BgCmd(char* lineSize, void* jobs)
{

	char* Command;
	char* delimiters = " \t\n";
	char *args[MAX_ARG];
	if (lineSize[strlen(lineSize)-2] == '&')
	{
		lineSize[strlen(lineSize)-2] = '\0';
		// Add your code here (execute a in the background)

		/*
		your code
		*/

	}
	return -1;
}

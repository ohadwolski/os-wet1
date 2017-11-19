//		commands.c
//********************************************
#include "commands.h"
#include <unistd.h>
using namespace std;
//********************************************
// globals

static char prevPath[MAX_LINE_SIZE] = {NULL}; // used inorder to maintain previous path
//********************************************
// function name: ExeCmd
// Description: interperts and executes built-in commands
// Parameters: pointer to jobs, command string
// Returns: 0 - success,1 - failure
//**************************************************************************************
int ExeCmd(jobs_list* jobs, char* lineSize, char* cmdString)
{
	char* cmd;
	char* args[MAX_ARG];
	char pwd[MAX_LINE_SIZE];
	char* delimiters = " \t\n";
	int i = 0, num_arg = 0;
	bool illegal_cmd = false; // illegal command
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
	if (!strcmp(cmd, "cd"))
	{
		if (num_arg !=1)
		{
			illegal_cmd = true;
		} else
		{
			getcwd(pwd, MAX_LINE_SIZE); 				// getting current directory
			if (strcmp(args[1], "-"))					// change to previous dir
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
				if (chdir(args[1]) == -1)
				{
					cout << "smash error: > " << args[1] << " - path not found" << endl;
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
			illegal_cmd = true;
		} else
		{
			cout << getcwd(pwd, MAX_LINE_SIZE) << endl;
		}
	}
	/*************************************************/
	else if (!strcmp(cmd, "history"))
	{
		if (num_arg != 0)
		{
			illegal_cmd = true;
		} else
		{
			history->print();
		}
	}

	/*************************************************/
	else if (!strcmp(cmd, "kill"))
	{
		if (num_arg !=2 || *args[1] != '-' || atoi(args[1]+1)) == 0 || atoi(arg[2]) == 0)
		{
			illegal_cmd = true;
		} else
		{
			int sig_num = atoi(arg[1]+1);
			int job_id = atoi(arg[2]);
			job* job_p = jobsList->find_job(job_id);
			if (job_p == NULL)
			{
				cout << "smash error: > kill" << job_id << " - can't find job" << endl;
				return 1;
			}
			if (kill(job_p->getPId(), sig_num) == -1)
			{
				cout << "smash error: > kill" << job_id << " - can't send signal" << endl;
				return 1;
			}

			cout << "signal " << sig_num << "was sent to pid " << job_p->getPId() << endl;

			if (sig_num == 18 || sig_num == 19 || sig_num == 20) // if stopped or continued. update.
			{
				job_p->changeStopped();
			}
		}
	}
	/*************************************************/
	else if (!strcmp(cmd, "mv"))
	{
		if (num_arg != 2)
		{
			illegal_cmd = true;
		} else
		{
			if (rename(args[1], args[2]) !=0)
			{
				perror("Error: command mv failed");
				return 1;
			}
			cout << args[1] << "has been renamed to " << args[2] << endl;
		}
	}
	/*************************************************/

	else if (!strcmp(cmd, "jobs"))
	{
		if (num_arg != 0)
		{
			illegal_cmd = true;
		} else
		{
			jobs->print();
		}
	}
	/*************************************************/
	else if (!strcmp(cmd, "showpid"))
	{
		if (num_arg != 0)
		{
			illegal_cmd = true;
		} else
		{
			cout << "smash pid is " << getpid() << endl;
		}
	}
	/*************************************************/
	else if (!strcmp(cmd, "fg"))
	{
		if (num_arg > 1)
		{
			illegal_cmd = true;
		} else
		{
			job* job_to_fg;
			if (num_arg == 0)
			{
				job_to_fg = jobs->get_last_job()

			} else
			{
				if (atoi(args[1]) == 0 || jobs->find_job(atoi(args[1])) == NULL)
				{
					cout << "smash error: > fg - invalid job number" << endl;
					return 1;
				}
				job_to_fg = jobs->find_job(atoi(args[1]));
			}
			int id = job_to_fg->getId();
			int pid = job_to_fg->getPId();
			char* name = job_to_fg->getName();
			bool stopped_status = job_to_fg->getStopped();

			cout << name << endl;
			if (kill(pid, SIGCONT) == -1)
			{
				perror("Can't send SIGCONT");
				return 1;
			}

			cout << "smash > signal SIGCONT sent to pid " << pid << endl;

			job job_c = new job(id ,pid, name);
			jobs->rmJob(id);
			int status;
			if (waitpid(pid, &status , WUNTRACED) == -1) // waiting till stopped or exited
			{
				perror("smash error:> waitpid failed");
				delete job_c;
				return 1;
			} else if (WIFSTOPPED(status)) // if stopped than add to job list again
			{
				if (stopped_status == false)
					job_c->changeStopped();
				jobs->addJob(job_c);
			}
			delete job_c;
			//sending signal SIGCONT
			//print job name
			// remove from list, copy to local job
			// wait for job to return
			// if stopped by ctrlz than add to jobs list with stopped
		}
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
	if (illegal_cmd == true)
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
int BgCmd(char* lineSize, jobs_list* jobs)
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

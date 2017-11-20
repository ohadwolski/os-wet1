// signals.c
// contains signal handler funtions
// contains the function/s that set the signal handlers

/*******************************************/
/* Name: handler_cntlc
   Synopsis: handle the Control-C */
#include "signals.h"




//**************************************************************************************
// function name: ctrlC_Hndlr
// Description: handler for the CTRL+C
// Parameters: signal number
// Returns: -
//**************************************************************************************
void ctrlC_Hndlr(int sig)
{
    printf("\b\b");  //canceling the ^C that is being printed
    if ((sig == SIGINT) && (running_in_fg != 0))
    {
        if (kill(running_in_fg,SIGINT) == -1)
		{
            perror("kill failed during handling SIGINT signal\n");
		}
        else
		{
			cout << "smash > A signal SIGINT (CTRL+C) was sent to process: " << running_in_fg << endl;
			remove_fg();

			// running_in_fg = 0;
			// free(running_in_fg_name);
			// running_in_fg_name = NULL;
		}
    }
}

//**************************************************************************************
// function name: ctrlZ_Hndlr
// Description: handler for CTRL+Z
// Parameters: signal number
// Returns: -
//**************************************************************************************
void ctrlZ_Hndlr(int sig)
{
    printf("\b\b");  //canceling the ^Z that is being printed
    if ((sig == SIGTSTP) && (running_in_fg != 0))
    {
        if (kill(running_in_fg,SIGTSTP) == -1)
		{
			perror("kill failed during handling SIGTSTP signal\n");
		}
		else
		{

			move_fg_to_bg()
			cout << "smash > A signal SIGTSTP (CTRL+Z) was sent to process: " << running_in_fg << endl;
			job* job_c = new job(jobs->getNextJobNum(), running_in_fg, running_in_fg_name);

			// job_c->changeStopped();
			// jobs->addJob(job_c);
			// delete job_c;
			// running_in_fg = 0;
			// free(running_in_fg_name);
			// running_in_fg_name = NULL;
		}
	}
}

//#include "signals.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
//quit_kill_test
//void handler(int sig_num);
void handler(int sig_num);


int main()
{

  struct sigaction sig;
  sigfillset(&sig.sa_mask);
  sig.sa_flags = SA_RESTART;
  sig.sa_handler = &handler;
  sigaction(SIGTSTP,&sig,NULL);
  while(1)
  {

  }
}

void handler(int sig_num)
{
    if(sig_num==SIGTSTP )
         printf("i got SIGTSTP\n");
    printf("sig num: %d", sig_num);
}
//     struct sigaction SIGTERMact;
// 	 //intializing SIGINTact
// 	 sigfillset(&SIGTERMact.sa_mask);
// 	 SIGTERMact.sa_flags = SA_RESTART;
// 	 SIGTERMact.sa_handler = &handler;
// 	 sigaction(SIGTERM,&SIGTERMact,NULL);
//     while(1)
//     {
//
//     }
// }
// void handler(int sig_num)
// {
//     if(sig_num==SIGTERM )
//         printf("i got SIGTERM\n");
// }

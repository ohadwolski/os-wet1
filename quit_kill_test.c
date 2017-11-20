//#include "signals.h"
#include <stdio.h>
#include <unistd.h>

//quit_kill_test
//void handler(int sig_num);
int main()
{
  while(1)
  {
    
  }
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

#ifndef _HISTORY_H
#define _HISTORY_H
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <list>
#include <iostream>

#define MAX_LIST_SIZE 50
#define MAX_LINE_SIZE 80

class history_list
{
private:
  std::list<char*> list;
public:
  history_list();
  ~history_list();
  void add(char* command_string);
  void print();
};



#endif

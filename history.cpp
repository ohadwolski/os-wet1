//		history.cpp
//********************************************
#include "history.h"
#include <string.h>
using namespace std;
//********************************************
// globals


//**************************************************************************************
// function name: ~history_list
// Description: destructor
// Parameters: -
// Returns: -
//**************************************************************************************
history_list::~history_list()
{
  std::list<char*>::iterator it = list.begin();
  for (; it != list.end() ; it++)
  {
    free(*it);
  }
}
//**************************************************************************************
// function name: add
// Description: adds a command to the history list
// Parameters: command string
// Returns: -
//**************************************************************************************
void history_list::add(char* command_string)
{
  if (strcmp(command_string, "history") != 0) // we don't want history to be in the list
  {
    char* record = (char*)malloc(MAX_LINE_SIZE*sizeof(char));
    if (!record)
      cout << "malloc failed!" << endl;
    strcpy(record, command_string);

    if (list.size() < MAX_LIST_SIZE)
    {
      list.push_back(record);
    } else
    {
      free(list.pop_front());
      list.push_back(record);
    }
  }
}
//**************************************************************************************
// function name: print
// Description: prints history list, oldest to newest
// Parameters: -
// Returns: -
//**************************************************************************************
void history_list::print()
{
  std::list<char*>::iterator it = list.begin();
  for(;it != list.end(); it++)
  {
    cout << *it << endl;
  }
}

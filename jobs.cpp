//		jobs.cpp
//********************************************
#include "jobs.h"
#include <string.h>
#include <time.h>
#include <list>
using namespace std;
//********************************************
// globals


//**************************************************************************************
// function name: job
// Description: c-tor
// Parameters: pid_ number and job name_ and id num
// Returns: -
//**************************************************************************************
job::job(int id_, int pid_, char* name_)
{
  id = id_;
  pid = pid_;
  name = (char*)malloc(sizeof(char)*(strlen(name_)+1));
  if (!name) return;
  strcpy(name, name_);
  timer = time();
  stopped = FALSE;
}
//**************************************************************************************
// function name: ~job
// Description: d-tor
// Parameters: -
// Returns: -
//**************************************************************************************
job::~job()
{
  free(name);
}
//**************************************************************************************
// function name: print
// Description: prints job
// Parameters: -
// Returns: -
//**************************************************************************************
void job::print()
{
  cout << "[" << id << "] " << name << " : " << pid << " " << getRunningTime << "secs ";
  if (getStopped())
    cout << "(Stopped)";
  cout << endl;
}
//**************************************************************************************
// function name: getID
// Description: returns job id
// Parameters: -
// Returns: int
//**************************************************************************************
int job::getId()
{
  return id;
}
//**************************************************************************************
// function name: getPId
// Description: returns job pid
// Parameters: -
// Returns: int
//**************************************************************************************
int job::getPId()
{
  return pid;
}
//**************************************************************************************
// function name: getStopped
// Description: returns stopped status
// Parameters: -
// Returns: bool
//**************************************************************************************
bool job::getStopped()
{
  return stopped;
}
//**************************************************************************************
// function name: getName
// Description: return pointer to name char
// Parameters: -
// Returns: char*
//**************************************************************************************
char* job::getName()
{
  return name;
}
//**************************************************************************************
// function name: getRunningTime
// Description: return current running time of process
// Parameters: -
// Returns: double
//**************************************************************************************
double job::getRunningTime()
{
  return difftime(time(), timer);
}
//**************************************************************************************
// function name: changeStopped
// Description: flips stopped variable
// Parameters: -
// Returns: -
//**************************************************************************************
void job::changeStopped()
{
  if (stopped == TRUE)
    stopped = FALSE;
  else
    stopped = TRUE;
}


//**************************************************************************************
// function name:
// Description:
// Parameters: -
// Returns: -
//**************************************************************************************
//jobs_list();
//**************************************************************************************
// function name:
// Description:
// Parameters: -
// Returns: -
//**************************************************************************************
//~jobs_list();
//**************************************************************************************
// function name: print
// Description: prints job list
// Parameters: -
// Returns: -
//**************************************************************************************
void jobs_list::print()
{
  std::list<job*>::iterator it = jobsList.begin();
  for (; it != jobsList.end() ; it++)
  {
    job->print();
  }
}
//**************************************************************************************
// function name: find_job
// Description: return pointer to job with id. return NULL if not found. if id=0 Returns
//              pointer to last item on the list
// Parameters: id to fine
// Returns: pointer to job
//**************************************************************************************
job* jobs_list::find_job(int id)
{
  if (id == 0)
    return jobsList.end();
  std::list<job*>::iterator it = jobsList.begin();
  for (; it != jobsList.end(); it++)
  {
    if (it->getId() == id)
      return it;
  }
  return NULL;
}
//**************************************************************************************
// function name: addJob
// Description: adds job to bottom of list
// Parameters: pointer to job to add
// Returns: -
//**************************************************************************************
void jobs_list::addJob(job* job_)
{
  job job_c = new job(job_->getId(), job_->getPId(), job_->getName());
  jobsList->push_back(job_c);
}
//**************************************************************************************
// function name: rmJob
// Description: removes job with id from list.
// Parameters: id
// Returns: true if successful, false if can't find jobs
//**************************************************************************************
bool jobs_list::rmJob(int id)
{
  job* job_to_rm = jobsList->find_job(id);
  if (job_to_rm == NULL)
    return FALSE;
  delete job_to_rm;
  jobsList->erase(job_to_rm); // not sure if this works
  return TRUE;
}
//**************************************************************************************
// function name: get_last_job
// Description: get last job pointer
// Parameters:
// Returns: pointer to job or null
//**************************************************************************************
job* jobs_list::get_last_job()
{
  return jobsList.end();
}

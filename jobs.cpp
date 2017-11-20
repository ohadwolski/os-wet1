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
  timer = time(NULL);
  stopped = false;
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
  return difftime(time(NULL), timer);
}
//**************************************************************************************
// function name: changeStopped
// Description: flips stopped variable
// Parameters: -
// Returns: -
//**************************************************************************************
void job::changeStopped()
{
  if (stopped == true)
    stopped = false;
  else
    stopped = true;
}


//**************************************************************************************
// function name:
// Description:
// Parameters: -
// Returns: -
//**************************************************************************************
//jobs_list();
//**************************************************************************************
// function name: ~jobs_list
// Description: deletes the jobs from list
// Parameters: -
// Returns: -
//**************************************************************************************
void jobs_list::~jobs_list()
{
	std::list<job*>::iterator it = jobs.begin();
	for (; it != jobs.end() ; it++)
	{
		delete it;
	}
}
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
    it->print();
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
    return *(jobsList.end());
  std::list<job*>::iterator it = jobsList.begin();
  for (; it != jobsList.end(); it++)
  {
    if (*(it)->getId() == id)
      return *(it);
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
    return false;
  delete job_to_rm;
  jobsList->erase(job_to_rm); // not sure if this works
  return true;
}
//**************************************************************************************
// function name: get_last_job
// Description: get last job pointer
// Parameters:
// Returns: pointer to job or null
//**************************************************************************************
job* jobs_list::get_last_job()
{
  return *(jobsList.end());
}

//**************************************************************************************
// function name: get_last_stopped
// Description: get last job stopped pointer
// Parameters:
// Returns: pointer to job or null
//**************************************************************************************
job* jobs_list::get_last_stopped()
{
	std::list<job*>::iterator it = jobsList.end();
	 for (; it != jobsList.begin(); it--)
	 {
		 if (*(it)->getStopped())
		 {
			 return *(it);
		 }
	 }
	return NULL;
}

//**************************************************************************************
// function name: kill_all
// Description: sends SIGTERM to each process, waits 5 secs than sends SIGKILL
// Parameters:
// Returns: TRUE if all killed successfully else FALSE
//**************************************************************************************
bool jobs_list::kill_all()
{
	std::list<job*>::iterator it = jobsList.begin();
	for (; it != jobsList.end(); it++)
	{
		if (kill(*(it)->getPId(), SIGTERM) == -1)
		{
			perror("Failed sending SIGTERM to %d \n", *(it)->getPId());
			return false;
		}
		time_t term_time = time(NULL);
		*(it)->print();
		cout << "sending SIGTERM ...";

		bool terminated = false;
		while (time(NULL) - term_time <= 5)
		{
			//WNOHANG     return immediately if no child has exited
			int status = waitpid(*(it)->getPId(), NULL, WNOHANG);
			if (status == -1)
			{
				perror("Failed waiting to %d \n", *(it)->getPId());
				return false;
			} else if (status == *(it)->getPId())
			{
				cout << "done." << endl;
				terminated = true;
				break;
			}
		}

		if (!terminated)
		{
			cout << "(5 sec passed) Sending SIGKILL...";
			if (kill(*(it)->getPId(), SIGKILL) == -1)
			{
				perror("Failed sending SIGTKILL to %d \n", *(it)->getPId());
				return false;
			}
			cout << " done." << endl;
		}
	}
	return true;
}

//**************************************************************************************
// function name: getNextJobNum
// Description: get new job's number
// Parameters:
// Returns: int
//**************************************************************************************
int jobs_list::getNextJobNum()
{
	return (jobsList.size() + 1);
}

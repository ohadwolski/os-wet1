#ifndef _JOBS_H
#define _JOBS_H
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <list>
#include <iostream>
#include <time.h>

class jobs_list;
class job;




class jobs_list
{
private:
  std::list<job*> jobsList;
public:
  jobs_list() {};
  ~jobs_list();
  void print();
  job* find_job(int id);
  job* get_last_job();
  job* get_last_stopped();
  void addJob(job* job_);
  bool rmJob(int id);
  bool kill_all();
  int getNextJobNum();
};

class job
{
private:
  int id;
  int pid;
  char* name;
  time_t timer;
  bool stopped;
public:
  job(int id_ ,int pid_, char* name_);
  ~job();
  void print();
  int getId();
  int getPId();
  bool getStopped();
  char* getName();
  double getRunningTime();
  void changeStopped();
};


#endif

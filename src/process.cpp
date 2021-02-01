#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

//Add Constructor
Process::Process(int id)
{
  pid     = id;
  command = LinuxParser::Command(pid) ;
  user    = LinuxParser::User(pid);
  uptime  = LinuxParser::UpTime(pid);
  ram     = LinuxParser::Ram(pid);
  
  
}
// TODO: Return this process's ID
int Process::Pid() 
{ 
  return pid; 
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const
{ 
  vector<long int> Process_Values = LinuxParser::ProcessUtilization(pid);
  
  long int total_time = Process_Values[0] +  Process_Values[1] ; //total_time = utime + stime
  total_time = total_time +  Process_Values[2] + Process_Values[3];//total_time=total_time +cutime + cstime
  float starttime_div_Hertz = ((float)Process_Values[4]/(float)sysconf(_SC_CLK_TCK)) ;
  float seconds = (float)LinuxParser::UpTime()- starttime_div_Hertz ;//seconds=uptime - (starttime / Hertz)
  
  float CPU_Percentage =   (float) ( total_time / sysconf(_SC_CLK_TCK) ) / seconds; 

  return CPU_Percentage; 
}

// TODO: Return the command that generated this process
string Process::Command() 
{ 
  return command; 
}

// TODO: Return this process's memory utilization
string Process::Ram() const
{ 
  return ram.substr(0,7); 
}

// TODO: Return the user (name) that generated this process
string Process::User() 
{ 
  return user; 
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() 
{ 
  return uptime; 
}

// TODO: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const
{ 
  return (this->CpuUtilization() > a.CpuUtilization()); 
  //return this->Ram() < a.Ram();
  return true;
}
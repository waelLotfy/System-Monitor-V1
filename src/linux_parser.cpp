#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel >> version;
  }
  return version;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() 
{ string line, key , value;
  float MemTotal, MemFree, Buffers;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open())
  {
    while (std::getline(filestream, line))
    {
      std::istringstream linestream(line);
      while (linestream >> key >> value)
      {
        if (key == "MemTotal:" )
        {
          MemTotal = std::stof(value) ;
        }
        else if (key == "MemFree:")
        {
          MemFree = std::stof(value) ;
        }
        else if (key == "Buffers:")
        {
          Buffers = std::stof(value);
        }
        
      }

    }

  }

  float memoryUtilization = 1.0 - (MemFree / (MemTotal- Buffers ) ) ; 

  return memoryUtilization; 
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() /*const*/
{ 
  string line, totalUpTimeSystem, idleTime;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if(filestream.is_open())
  {
    if(std::getline(filestream,line))
    {
      std::istringstream linestream(line);
      linestream >> totalUpTimeSystem >> idleTime ;

    }

  }
  return std::stol(totalUpTimeSystem) ; 
}

// TODO: Read and return the number of jiffies for the system
//long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
//long LinuxParser::ActiveJiffies(int pid) { return 0; }

// TODO: Read and return the number of active jiffies for the system
//long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
//long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<int> LinuxParser::CpuUtilization() 
{ 
  string line, key;
  string CPU_Value;
  vector<int> CPU_Values = {0};
  
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open())
  {
    while(std::getline(filestream,line))
    {
    	std::istringstream linestream(line);
    	while (linestream >> key)
    	{
      		if(key == "cpu")
      		{
        		while(linestream >> CPU_Value)
        		{
          			CPU_Values.push_back(std::stoi(CPU_Value));
        		}
        		return CPU_Values;
      		}
        }
     }
  }
  
  return CPU_Values; 
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() 
{ string ProcessesNo;
  string key;
  string line;

  std::ifstream filestream(kProcDirectory + kStatFilename) ;
  if(filestream.is_open())
  {
    while (std::getline(filestream,line))
    {
      std::istringstream linestream(line) ;
      while(linestream >> key >> ProcessesNo)
      {
        if(key == "processes")
        {
          return std::stoi(ProcessesNo) ;

        }

      }

    }

  }
  return 0; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() 
{ 
  string Processesrunning;
  string key;
  string line;

  std::ifstream filestream(kProcDirectory + kStatFilename) ;
  if(filestream.is_open())
  {
    while (std::getline(filestream,line))
    {
      std::istringstream linestream(line) ;
      while(linestream >> key >> Processesrunning)
      {
        if(key == "procs_running")
        {
          return std::stoi(Processesrunning) ;

        }

      }

    }

  }
  return 0; 
}

// TODO: Read and return the command associated with a process
string LinuxParser::Command(int pid) 
{ 
  string line;

  std::ifstream filestream(kProcDirectory + to_string(pid) + kCmdlineFilename) ;
  if(filestream.is_open())
  {
    std::getline(filestream,line);
    return line;
  }
  else 
  {
    return string{};
  }
}

// TODO: Read and return the memory used by a process
string LinuxParser::Ram(int pid) /*const*/
{ 
  string value;
  string key;
  string line;
  double ramValue;

  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename ) ;
  if(filestream.is_open())
  {
    while (std::getline(filestream,line))
    {
      std::istringstream linestream(line) ;
      while(linestream >> key >> value)
      {
        if(key == "VmSize:")
        {
          ramValue = std::stof(value) / (float)1000.0 ;
          return to_string(ramValue) ;

        }

      }

    }

  }
    
  	return string{}; 
  

}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) 
{
  string uid;
  string key;
  string line;

  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename ) ;
  if(filestream.is_open())
  {
    while (std::getline(filestream,line))
    {
      std::istringstream linestream(line) ;
      while(linestream >> key >> uid)
      {
        if(key == "uid:")
        {
          return uid ;

        }

      }

    }

  }
  return uid; 
}

// TODO: Read and return the user associated with a process
string LinuxParser::User(int pid) 
{ 
  string line,name,password, uid;
  std::ifstream filestream(kPasswordPath);
  
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> name >> password >> uid) {
        if (uid == LinuxParser::Uid(pid)) {
          return name;
        }//end if 
      }// end inner while
    }// end outer while
  }// end first if
  return string{};
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long int LinuxParser::UpTime(int pid) 
{ 
  string key;
  string line;

  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename ) ;
  if(filestream.is_open())
  {
    int i = 1;
    while (std::getline(filestream,line))
    {
      std::istringstream linestream(line) ;
      while(linestream >> key )
      {
        if(i == 22)
        {
          return ( LinuxParser::UpTime() - (std::stol(key) / sysconf(_SC_CLK_TCK) ) );
        }
        i++;
      }
    }
  }
  return 0 ;  
}

//Return the process utilization based on the pid
std::vector<long int> LinuxParser::ProcessUtilization(int pid) /*const*/
{
  string key ; 
  string line;

  vector<long int> Process_Values = {0};

  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename ) ;
  if(filestream.is_open())
  {
    int i = 1;
    while (std::getline(filestream,line))
    {
      std::istringstream linestream(line) ;
      while(linestream >> key )
      {
        if(i == 14)
        {
          Process_Values.push_back(std::stol(key)) ; // utime = key;
        }
        
        if(i == 15)
        {
          Process_Values.push_back(std::stol(key)) ; //stime = key;
        }
        
        if(i == 16)
        {
          Process_Values.push_back(std::stol(key)) ; //cutime = key;
        }
        
        if(i == 17)
        {
          Process_Values.push_back(std::stol(key)) ; //cstime = key;
        }
        
        if(i == 22)
        {
          Process_Values.push_back(std::stol(key)) ; //starttime = key;
        }
        i++;
      }
    }
  }
  
  
  return Process_Values ;
  
}

#include "processor.h"


// TODO: Return the aggregate CPU utilization
float Processor::Utilization() 
{ 
  vector<int> CPU_Values = LinuxParser::CpuUtilization();
  
  unsigned long long int CurrentNonIdle = CPU_Values[LinuxParser::CPUStates::kUser_]       +        		CPU_Values[LinuxParser::CPUStates::kNice_] + CPU_Values[LinuxParser::CPUStates::kSystem_] +
CPU_Values[LinuxParser::CPUStates::kIRQ_] + CPU_Values[LinuxParser::CPUStates::kSoftIRQ_]   + CPU_Values[LinuxParser::CPUStates::kSteal_]    ;
  
  unsigned long long int CurrentIdle = CPU_Values[LinuxParser::CPUStates::kIdle_]       +        		CPU_Values[LinuxParser::CPUStates::kIOwait_] ;
  
  unsigned long long int CurrentTotal = CurrentNonIdle + CurrentIdle ;
  
  //# differentiate: actual value minus the previous one
  unsigned long long int Total = CurrentTotal - PrevTotal ;
  unsigned long long int Idle = CurrentIdle - PrevIdle ;

  float CPU_Percentage =  0.0;
  if(Total > 0)
  {
  	CPU_Percentage = ( (float)(Total - Idle) / Total ) ; 
  }

  PrevTotal = CurrentTotal; 
  PrevIdle  = CurrentIdle; 

  return CPU_Percentage; 
}
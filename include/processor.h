#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "linux_parser.h"
#include <vector>
using std::vector;

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  

  // TODO: Declare any necessary private members
 private:
  
  	unsigned long long int PrevTotal   , PrevIdle    ;
  

};

#endif
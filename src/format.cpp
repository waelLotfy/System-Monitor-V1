#include <string>

#include "format.h"
#include "iostream"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) 
{ 
    long hour,minute ;
    string format;
    minute  = seconds / 60;
    seconds = seconds % 60;

    hour   = minute / 60;
    minute = minute % 60 ;

    
    string hr  = std::to_string(hour);
    string min = std::to_string(minute);
    string sec = std::to_string(seconds);
  format = hr.insert(0, 2 - hr.length(), '0') + ":" + min.insert(0, 2 - min.length(), '0') + ":" + sec.insert(0, 2 - sec.length(), '0') ;
    

    return format; 
}
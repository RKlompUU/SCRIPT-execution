#include <scrpt_vrfy/logger.h>

#include <iostream>
using namespace std;

std::ostream &Logger::out = cout;

Logger::Logger(LogLevel l)
{
  if( l == L_NONE )
    return;
}

Logger::~Logger()
{
  out.flush();
}

void Logger::close()
{
  out << "System: logger shutdown\n---------------\n";
}

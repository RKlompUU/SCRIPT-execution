#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <iostream>

#include <errno.h>


enum LogLevel
{
  L_INFO,
  L_WARN,
  L_ERR,
  L_NONE
};

#define LOG_LEVEL        L_INFO

class Logger
{
public:
  Logger(LogLevel l);
  ~Logger();

  template<typename T>
  Logger& operator << (const T &object)
  {
    out << object;
    return *this;
  }

  static void close();

  static std::ostream &out;
};


#define log(level) \
  if( level < LOG_LEVEL )\
  ; \
  else \
    Logger(level)

#endif

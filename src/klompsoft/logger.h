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
  Logger(LogLevel l, const char *customprepend=0, bool appendLineEnd = false);
  ~Logger();

  template<typename T>
  Logger& operator << (const T &object)
  {
    if( c++ == 0 )
    {
      out << prepend;
    }
    out << object;
    return *this;
  }

  static void close();

  static std::ostream &out;

  int c;
  std::string prepend;
  bool appendLineEnd;
};


#define log(level) \
  if( level < LOG_LEVEL )\
  ; \
  else \
    Logger(level)

#endif

#include <klompsoft/logger.h>

#include <iostream>
using namespace std;

std::ostream &Logger::out = cout;
//std::ofstream Logger::out("/home/rklomp/.bitcoin.txt", std::ios_base::app | std::ios_base::out);

#include <sys/time.h>

#define TIMESTAMP_STRLEN 21
#define TIMESTAMP_FORMAT "%H:%M:%S."

Logger::Logger(LogLevel l, const char *customPrepend, bool appendLineEnd)
: c(0)
, appendLineEnd(appendLineEnd)
{
  if( l == L_NONE )
    return;

  // time_t t = time(0);
  // char timebuff[TIMESTAMP_STRLEN];
  // strftime( timebuff, TIMESTAMP_STRLEN, TIMESTAMP_FORMAT, localtime(&t) );
  //
  // prepend = timebuff;
  // timeval tv;
  // gettimeofday( &tv, NULL );
  // std::string msStr = std::to_string( tv.tv_usec/1000 );
  // prepend += std::string( 3 - msStr.length(), '0' ) + msStr;
  // prepend += " ";
  if( customPrepend != NULL )
    prepend += customPrepend;
  // switch( l )
  // {
  // case L_INFO:
  //   prepend += "info: ";
  //   break;
  // case L_WARN:
  //   prepend += "warning: ";
  //   break;
  // case L_ERR:
  //   prepend += "error: ";
  //   break;
  // default:
  //   break;
  // }
//  mutex->lock();
}

Logger::~Logger()
{
  if( appendLineEnd )
    out << "\n";
  out.flush();
//  mutex->unlock();
}

void Logger::close()
{
  out << "System: logger shutdown\n---------------\n";
//  out.close();
}

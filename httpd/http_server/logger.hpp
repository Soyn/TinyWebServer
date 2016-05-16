#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED
/***********************
* @Author: Soyn
* @Brief: Logging the activity of http server.
* @CreatedTime: 1/11/15
* @Refactor: Soyn at 5/5/16
************************/
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#include <string>
#include <iostream>
#include <fstream>

class Logger{
public:
    Logger(){}
    ~Logger(){}
    //
    // @Brief: The handling procedure
    void Logging(int type, const std::string s1, const std::string s2,
                 int socket_file_descriptor);
    enum LoggerStatusCode{ERROR = 42, LOG = 44, FORBIDDEN = 403, NOTFOUND = 404};
};

#endif // LOGGER_H_INCLUDED

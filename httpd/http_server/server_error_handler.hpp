#ifndef SERVER_ERROR_HANDLER_H_INCLUDED
#define SERVER_ERROR_HANDLER_H_INCLUDED

/**************************************
* @Author: Soyn
* @Brief: The error handler for http server
* @CreatedTime: 30/4/16.
****************************************/
#include <string.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>


extern std::map<std::string, std::string> SupportFileType;
class ErrorHandler{
public:
    ErrorHandler():argument_counts_(1), arguments_values_(nullptr){}
    ErrorHandler(int argc, char **argv):argument_counts_(argc),
                                        arguments_values_(argv){ }

    ~ErrorHandler(){}

    //
    // @Brief: For not support error
    void CheckRequestSupportedOrNot();
    //
    // @Brief: Check the request file's directory is valid or not
    void CheckRequestDirectoryValidOrNot();
    //
    // @Brief: Check the change directory action is valid or not.
    void CheckChangeDirectoryValidOrNot();


    static const double version_;
private:
    int argument_counts_;
    char **arguments_values_;
};

#endif // SERVER_ERROR_HANDLER_H_INCLUDED

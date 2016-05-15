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



typedef struct SupportFileType{
    std :: string file_extension_;
    std :: string file_type_;
}SFT;


class ErrorHandler{
public:
    ErrorHandler(int argc, char **argv) : argument_counts_(argc),
                                        arguments_values_(argv){ }
    ~ErrorHandler(){}

    //
    // @Brief: For not support error
    void CheckRequestSupportedValidOrNot();
    //
    // @Brief: Check the request file's directory is valid or not
    void CheckRequestDirectoryValidOrNot();
    //
    // @Brief: Check the change directory action is valid or not.
    void CheckChangeDirectoryValidOrNot();

    static const SFT supported_file_type_collections_[];
    static const double version_;
private:
    int argument_counts_;
    char **arguments_values_;
};

#endif // SERVER_ERROR_HANDLER_H_INCLUDED

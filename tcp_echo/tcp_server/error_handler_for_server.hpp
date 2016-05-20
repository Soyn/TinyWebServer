#ifndef ERROR_HANDLER_H_INCLUDED
#define ERROR_HANDLER_H_INCLUDED

/**************************************
* @Author: Soyn
* @Brief:The error handler for my server.
* @CreatedTime: 29/3/16.
****************************************/
#include <cstdio>
#include <cstdlib>
#include <cerrno>

#include <string>

class ErrorHandler{
public:
    //
    // @Brief: The conctructor takes socket file description.
    ErrorHandler(int argument_counts) : argument_counts_(argument_counts){};
    //
    // @Brief: Check port error. If argument's counts less than 2, exit.
    void CheckPortOpenOrNot();
    //
    // @Brief: Check the socket is created or not.
    void CheckSocketCreatedOrNot(int const &socket_file_description);
    //
    // @Brief: Check the socket is binded or not.
    void CheckBindOrNot(int &bind_flag);
    //
    // @Brief: Check the server accept the request or not.
    void CheckAcceptOrNot(int const &new_socket_file_description);
    //
    // @Brief: The error display function for server.
    void ErrorMessageDisplay(std :: string const &message) {
        Error(message.c_str());
    }
    ~ErrorHandler(){}
private:
    int argument_counts_;
    void Error(const char *message);

};
#endif // ERROR_HANDLER_H_INCLUDED

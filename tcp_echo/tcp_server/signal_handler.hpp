#ifndef SIGNAL_CATCH_H_INCLUDED
#define SIGNAL_CATCH_H_INCLUDED

/******************************
* @Author: Soyn.
* @Brief: Add the signal hander
* @CreatedTime: 3/5/16
******************************/

#include <sys/wait.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <iostream>
//
// use typedef to simplify the signal()
typedef void SignalFunction(int);
class SignalHandler{
public:
    //
    SignalHandler() = default;
    //
    // To define the my own signal handler function
    SignalFunction* Signal(int signal, SignalFunction *func);
    ~SignalHandler(){}

};

//
// @Brief: the handle function
void SignalChild(int signo);
#endif // SIGNAL_CATCH_H_INCLUDED

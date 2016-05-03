#ifndef SIGNAL_CATCH_H_INCLUDED
#define SIGNAL_CATCH_H_INCLUDED

/******************************
* @Author: Soyn.
* @Brief: Add the signal hander
* @CreatedTime: 3/5/16
******************************/

#include <sys/wait.h>
#include <sys/signal.h>

#include <iostream>

class SignalHandler{
public:
    //
    // use typedef to simplify the signal()
    typedef void SignalFunction(int);

    //
    // To define the my own signal handler function
    SignalFunction* Signal(int signal, SignalFunction *funcion);
    SignalHandler();
    ~SignalHandler();
};

#endif // SIGNAL_CATCH_H_INCLUDED

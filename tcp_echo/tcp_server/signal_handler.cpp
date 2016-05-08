/**********************************************
* @Author: Soyn
* @Brief: The implementation of signal handler
* @CretaedTime: 3/5/16
***********************************************/

#include "signal_handler.h"
//
// @Brief: The signal handler function
SignalHandler :: SignalFunction *
SignalHandler :: Signal(int signo, SignalFunction *func)
{
    struct sigaction active, old_active;
    active.sa_handler = func;
    sigemptyset(&active.sa_mask);
    active.sa_flags = 0;
    if(signo == SIGALRM){
#ifdef SA_INTERRUPT
        active.sa_flags != SA_INTERRUPT;
#endif // SA_INTERRUPT
    }else{
#ifdef SA_RESTART
        active.sa_flags |= SA_RESTART;
#endif // SA_RESTART
    }

    if(sigaction(signo, &active, &old_active) < 0){
        return (SIG_ERR);
    }
    return (old_active.sa_handler);
}

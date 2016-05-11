/************************************************
* @Author: Soyn
* @Brief: The implement for client error handler
* @CreatedTime: 15/9/15
* @Soyn: Refactor the code in 25/4/16.
************************************************/

#include "error_handle_for_client.h"
#include <cerrno>
#include <iostream>
//
// @Brief: Constructor tales argument counts and argument values from command
ClientErrorHandler :: ClientErrorHandler(int argument_counts,
                    char **argument_values) :
                    argument_counts_(argument_counts),
                         argument_values_(argument_values){}

//
// @Brief: Underlying error message handler
void ClientErrorHandler :: Error(const char *message)
{
    perror(message);
    exit(1);
}
//
// Check the command line inputs
void ClientErrorHandler :: CheckHost()
{
    if(argument_counts_ < 3){
        std :: cerr << "Usage " << argument_values_[0]
                    << " hostname port" << std :: endl;
        exit(0);
    }
}

//
// @Brief: Check the client socket created or not.
void ClientErrorHandler ::
    CheckSocketCreatedOrNot(const int &socket_file_description)
{
    if(socket_file_description < 0){
        Error("Error creating socket");
    }
}

//
// @Brief: Check the connection established or not
void ClientErrorHandler :: CheckConnection(const int &connection_status)
{
    if(connection_status < 0)
        Error("Error connecting");
}
//
// @Brief: Check writing succeed or not
// @Para name: return_value => return from write()
void ClientErrorHandler :: WritingError(const int &writing_return_value)
{
    if(writing_return_value < 0){
        Error("Error on writing");
    }
}

//
// @Brief: Check the host
void ClientErrorHandler :: HostNameError(const hostent *server)
{
    if(!server){
        std :: cerr << "No such host" << std :: endl;
    }
}

//
// @Brief: Check Reading error
void ClientErrorHandler :: ReadingError(const int &reading_return_value)
{
    if(reading_return_value < 0){
        Error("Error connection");
    }
}

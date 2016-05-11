/******************************************
* @Author: Soyn
* @Brief: The implement for error handler.
* @CreatedTime: 29/3/16.
******************************************/
#include "error_handler_for_server.h"
#include "signal_handler.h"
#include <iostream>
//
// @Brief: The private function for error handling.
void ErrorHandler :: Error(const char* message)
{
    std :: perror(message);
    exit(1);
}

//
// @Brief: Handle the port error
void ErrorHandler :: CheckPortOpenOrNot()
{
    if(argument_counts_ < 2){
        std :: cerr << "Error, no port provided\n" << std :: endl;
        exit(1);
        }
}

//
// @Brier: Handle the open error.
// @Note: If socket opens successfully, sockfd
void ErrorHandler :: CheckSocketCreatedOrNot(int const &socket_file_description)
{
    if(socket_file_description < 0)
        ErrorMessageDisplay("ERROR opening socket");
}

//
// @Brief: Check bind the socket with server or not.
void ErrorHandler :: CheckBindOrNot(int &bind_flag)
{
    if(bind_flag < 0)
        ErrorMessageDisplay("ERROR on binding");
}

// @Brief: Check the server accept the request from client or not.
void ErrorHandler :: CheckAcceptOrNot(int const &new_socket_file_description)
{
    if(new_socket_file_description < 0)
        ErrorMessageDisplay("ERROR on accept");
}

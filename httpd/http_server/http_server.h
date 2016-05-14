/*************************************************************************
* @Author: Soyn
* @Brief: The simple http server.
* @CreatedTime: Sat 31 Oct 2015 09:50:30 AM CST
* @Refactor by Soyn at 31/4/16
 ************************************************************************/

#ifndef _HTTPSERVER_H
#define _HTTPSERVER_H

#include "tcp_socket.h"
#include "server_error_handler.h"

#include <string.h>
#include <cstdlib>
#include <cstdio>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <memory>
#include <algorithm>
#include <map>



class HttpServer :: TcpSocket{
public:

    HttpServer(int argument_counts, char **argument_values) :
        TcpSocket(argument_counts, argument_values), argument_counts_(argument_counts_),
        argument_values_(argument_values),
        error_handler_(argument_counts_, argument_values_){}

    ~HttpServer(){}

    //
    // @Brief: Open the server for connection
    void OpenServer();

    //
    // @Brief: Initialize the server
    void InitializeServer();

    //
    // @Brief: Get the request from client
    void GetRequest();
    //
    // @Brief: Send the response to client

    //
    // @Brief: the predictor function
    inline bool IsDelimiter(const char &chr);
    //
    // @Brief: Handle the request from client
    // @Para name = "connected_file_description": the connected file
    // description returned from accept()
    void HandleRequest(const int connected_socket_file_description,
                        int hit);

    void SendResponse();

private:

    static const int BufferSize, Error, Forbidden, NotFound, Log;

    int argument_counts_;
    char **argument_values_;

    ErrorHandler error_handler_;
    Logger logger_;

};
#endif

/*************************************************************************
* @Author: Soyn
* @Brief: The simple http server.
* @CreatedTime: Sat 31 Oct 2015 09:50:30 AM CST
* @Refactor by Soyn at 31/4/16
 ************************************************************************/

#ifndef _HTTPSERVER_H
#define _HTTPSERVER_H

#include "logger.hpp"
#include "tcp_socket.hpp"
#include "server_error_handler.hpp"



#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <memory>
#include <algorithm>
#include <map>

class TcpSocket;

class HttpServer:public TcpSocket{
    friend bool IsDelimiter(const char &chr);
public:

    HttpServer(int argument_counts, char **argument_values) :
        TcpSocket(argument_counts, argument_values), argument_counts_(argument_counts),
        argument_values_(argument_values),
        error_handler_(argument_counts_, argument_values_){}
    HttpServer(const HttpServer&) = delete;
    HttpServer& operator=(const HttpServer&) = delete;
    ~HttpServer(){}

    //
    // @Brief: Open the server for connection
    void OpenServer();

    //
    // @Brief: Initialize the server
    void InitializeServer();

    //
    // @Brief: Get the request from client
    void GetRequest(const int& connected_socket_file_descriptor, int hit);
    //
    // @Brief: Handle the request from client
    // @Para name = "connected_file_description": the connected file
    // description returned from accept()
    void HandleRequest(const int& connected_socket_file_descriptor,int hit);
    //
    // @Brief: Send response to client
    void SendResponse();

    //
    // @Brief: Run the server
    void Run();

private:

    static const int BufferSize;
    int argument_counts_;
    char **argument_values_;

    ErrorHandler error_handler_;
    Logger logger_;
    //
    // @Brief: buffer for socket descriptor
    std::string buffer_;
    std::string request_file_type_;
    int length_of_request_file_;

    //
    //@Brief: Get http head information
    void GetHttpHeadInfo(const int& connected_socket_file_descriptor,
                        const int& hit);

    //
    // @Brief: Send http head info
    void SendHttpHead(const int& connected_socket_file_descriptor);

    //
    // @Brief: Send request file to client
    void SendRequestFile(const int& connected_socket_file_descriptor);
};


#endif

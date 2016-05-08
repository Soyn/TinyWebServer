#ifndef TCP_SOCKET_H_INCLUDED
#define TCP_SOCKET_H_INCLUDED
/******************************
* @Author: Soyn
* @Brief: tcp socket server for http server
* @CreatedTime: 4/5/16
******************************/
#include "logger.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <iostream>

class TcpSocket{
public:
    TcpSocket(int argument_counts, char **argument_values) :
        argument_counts_(argument_counts), argument_values_(argument_values),
    ~TcpSocket(){}
    void CreateSocket();
private:
    int argument_counts_;
    char **argument_values_;

    int port_number_, listen_file_description_,
    connected_socket_file_description_;

    socklen_t length;
    sockaddr_in client_address, server_address_;

    Logger logger_;
};


#endif // TCP_SOCKET_H_INCLUDED

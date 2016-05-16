#ifndef TCP_SOCKET_H_INCLUDED
#define TCP_SOCKET_H_INCLUDED
/******************************
* @Author: Soyn
* @Brief: tcp socket server for http server
* @CreatedTime: 4/5/16
******************************/
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
#include <sys/stat.h>

#include "logger.hpp"
#include <iostream>

class TcpSocket{
public:
    TcpSocket(int argument_counts, char **argument_values) :
        argument_counts_(argument_counts), argument_values_(argument_values){}

    TcpSocket(const TcpSocket&) = delete;
    TcpSocket& operator=(const TcpSocket&) = delete;

    ~TcpSocket(){}
    void CreateSocket();
public:
    int argument_counts_;
    char **argument_values_;

    int port_number_, listen_socket_file_descriptor_,
    connected_socket_file_descriptor_;

    socklen_t length;
    sockaddr_in client_address_, server_address_;

    Logger logger_;
};


#endif // TCP_SOCKET_H_INCLUDED

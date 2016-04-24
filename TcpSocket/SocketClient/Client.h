#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>

/**
* A simple client using socket.
* Created by Soyn.15/09/15.
**/
class Client{
public:
    Client(int, char **);
    ~Client();
    void error(const char* msg);
    void HostHoding();
    void OpeningSockError();
    void HostNameError();
    void WritingError();
    void ReadingError();
    void EstablishedSocket();
    void GetHostName();
    void setServeraddr();
    void Connect();
    void GetMsg();
    void ReadMsg();
    void Run();

private:
    int sockfd, portno, n, argc;
    sockaddr_in serv_addr;
    hostent *server;
    char buffer[256], **argv;
};
#endif // CLIENT_H_INCLUDED

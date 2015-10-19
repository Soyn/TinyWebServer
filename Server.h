#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

/**
* The server.h
* Created by Soyn.25/9/15.
**/

class Server{
public:
    Server(int argc, char **argv);
    ~Server();
    void PortError();
    void OpenSockError();
    void BindError();
    void AcceptError();
    void CreateSocket();
    void SetServerAdd();
    void EstablishConnect();
    void Run();
    void error(const char*);
    void dostuff(int&);
private:
    int sockfd, newsockfd, portno, argc,pid;
    socklen_t clilen;
    char **argv;
    sockaddr_in serv_addr, cli_addr;
};


#endif // SERVER_H_INCLUDED

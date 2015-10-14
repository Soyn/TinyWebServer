#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#ifndef SERVER_CPP_H_INCLUDED
#define SERVER_CPP_H_INCLUDED

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
    Server(int argc, char *(argv[]));
    ~Server();
    void PortError();
    void OpenSockError();
    void BindError();
    void AcceptError();
    void ReadingError();
    void WritingError();
    void CreateSocket();
    void SetServerAdd();
    void EstablishConnect();
    void ReadMessage();
    void WriteMessage();
    void Run();
    void error(const char*);
    void dostuff(int sock);
private:
    int sockfd, newsockfd, portno, argc,pid,n;
    socklen_t clilen;
    char **argv, buffer[256];
    sockaddr_in serv_addr, cli_addr;
};


#endif // SERVER_CPP_H_INCLUDED







#endif // SERVER_H_INCLUDED

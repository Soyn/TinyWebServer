/*************************************************************************
	> File Name: HttpServer.h
	> Author: Soyn
	> @Brief: The simple http server.
	> Created Time: Sat 31 Oct 2015 09:50:30 AM CST
 ************************************************************************/

#ifndef _HTTPSERVER_H
#define _HTTPSERVER_H
#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>  /*for open(),creat()*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <arpa/inet.h>
#include <map>
#include <errno.h>
#include <sstream>
#include <fcntl.h> /*for O_RDWR*/
#include <memory>

#define VERSION 1.0
#define BUFFSIZE 8096
#define ERROR 42
#define LOG 44
#define FORBIDDEN 403
#define NOTFOUND 404



class Error;
class HttpServer{
public:
    HttpServer(){}
    ~HttpServer(){}
    void Web(int,int);
    void Logger(const int&, const std :: string, const std :: string ,int);
    void InsertPacket();
    void CreateSocket();
    void ForkProcess();
    void SetUpSocket();
    void SetUpSocketAddress();
    void EstablishConnect();


    int argc;
    char ** argv;
private:

    std :: map<int,std :: string> Packets;
    int port,pid,listenfd,socketfd,hit;
    socklen_t length;
    sockaddr_in cli_addr,serv_addr;
};

class Error{
public:
    Error(){}
    ~Error(){}
    void NotSupportError();
    void DirectoryError();
    void ChangeDirectoryError();


    int argc;
    char **argv;
};

class Main{
public:
    /*initialize the data*/
    Main(int, char **);
    void RunServer();
    ~Main(){}
private:
    HttpServer MyServer;
    Error e;
};
#endif

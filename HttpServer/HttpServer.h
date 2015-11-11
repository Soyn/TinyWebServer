/*************************************************************************
	> File Name: HttpServer.h
	> Author:
	> Mail:
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
    friend class Error;
    HttpServer(){}
    HttpServer(int arc,char**arv):argc(arc),argv(arv){}
    ~HttpServer(){}
    void Web(int,int);
    void Logger(const int&, std :: string, std :: string ,int);
    void InsertPacket();
    void CreateSocket();
    void ForkProcess();
    void SetUpSocket();
    void SetUpSocketAddress();
    void EstablishConnect();
private:

    std :: map<int,std :: string> Packets;
    int argc;
    char **argv;
    int port,pid,listenfd,socketfd,hit;
    /*static initialised to zero*/
    socklen_t length;
    sockaddr_in cli_addr,serv_addr;
};

class Error{
public:
    Error(){}
    Error(HttpServer &tmp):argc(tmp.argc),argv(tmp.argv){}
    ~Error(){}
    void NotSupportError();
    void DirectoryError();
    void ChangeDirectoryError();
private:
    int argc;
    char **argv;
};
#endif

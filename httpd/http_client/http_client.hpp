#ifndef HTTPCLIENT_HPP_INCLUDED
#define HTTPCLIENT_HPP_INCLUDED
/***********************************************
* FileName: HttpClient.cpp
* Author: Soyn
* @Brief: The simple client using http protocol.
* Created Time: 23/11/15
************************************************/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define PORT 8181
#define IP_ADDRESS "192.168.0.95"
#define BUFSIZE 8196



class HttpClient{
public:
    /*Constructor*/
    HttpClient(){};
    HttpClient(int, char **);
    ~HttpClient(){}
    void pexit(const std :: string&);
    void WelcomeSocket(); // for welcome
    void InitBaseData(); //initialize the data
    void Connect();
    void WriteSocket();
    void RunClient();
private:
    int argc;
    char **argv;
    int socketfd;
    std :: string buffer;
    sockaddr_in serv_addr;
};


#endif // HTTPCLIENT_HPP_INCLUDED


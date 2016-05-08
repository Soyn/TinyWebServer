#include "HttpClient.h"

std :: string command("GET/index.html HTTP/1.0 \r\n\r\n");

HttpClient :: HttpClient(int _argc, char **_argv)
{
    argc = _argc;
    argv = _argv;
}

///
/// <summary>Help function for exiting</summary>
///

void HttpClient :: pexit(const std :: string& str)
{
    perror(str.c_str());
    exit(1);
}

///
/// <summary> for welcome connect using TCP </summary>
///

void HttpClient :: WelcomeSocket()
{
    std :: cout << "client trying to connect to " << IP_ADDRESS << " and port " << PORT << std :: endl;
    if((socketfd = socket(AF_INET, SOCK_STREAM,0)) < 0){
        pexit("socket() failed");
    }
}

///
/// <sumary> to initialize the base data</summary>
///

void HttpClient :: InitBaseData()
{
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    serv_addr.sin_port = htons(PORT);
}

void HttpClient :: Connect()
{
    if(connect(socketfd,(sockaddr*) &serv_addr, sizeof(serv_addr)) < 0){
        pexit("connect failed");
    }

    std :: cout <<  "Send bytes = " << command.length() << command << std :: endl;
}

void HttpClient :: WriteSocket()
{
    int i;
    write(socketfd, command.c_str(), command.length());

    while(( i = read(socketfd,(void*) buffer.c_str(), BUFSIZE))){
        write(1,buffer.c_str(),i);
    }
}

void HttpClient :: RunClient()
{
    WelcomeSocket();
    InitBaseData();
    Connect();
    WriteSocket();
}

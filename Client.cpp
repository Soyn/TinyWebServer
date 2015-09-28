#include "Client.h"
#include <cerrno>
#include <cstdio>

/**
* Simple web server
* Created by Soyn.15/09/15.
**/

///constructor
Client :: Client(int argc, char **argv)
{
    this -> argv = argv;
    this -> argc = argc;
}

///desconstructor
Client :: ~Client()
{
    close(sockfd);
}

void Client::error(const char *msg)
{
    perror(msg);
    exit(1);
}

void Client :: HostHoding()
{
    if(argc < 3)
    {
        std :: cerr << "Usage " << argv[0] << "hostname port" << std :: endl;
        exit(0);
    }
}

void Client :: OpeningSockError()
{
    if( sockfd < 0)
        error("ERROR opeing socket");
}

void Client :: WritingError()
{
    if( n < 0)
        error("ERROR writing to socket");
}
void Client ::  HostNameError()
{
    if(server == NULL)
    {
        std :: cerr << "No such host" << std :: endl;
        exit(0);
    }
}

void Client :: ReadingError()
{
    if( connect(sockfd, (sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting");
}

void Client ::  EstablishedSocket()
{
    portno = std :: atoi(argv[2]);  //convert the port number from string of digits to an interger
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    OpeningSockError();
}

void Client :: GetHostName()
{
    server = gethostbyname(argv[1]);
    HostNameError();
}

void Client :: setServeraddr()
{
    bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char*)server -> h_addr, (char*)&serv_addr.sin_addr.s_addr, server -> h_length);
    serv_addr.sin_port = htons(portno);
}

void Client :: Connect()
{
    if( connect(sockfd, (sockaddr*)&serv_addr, sizeof( serv_addr)) < 0)
        error("ERROR connecting");
}

void Client :: GetMsg()
{
    std :: cout << "Please enter the message: " ;
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
    n = write(sockfd, buffer, strlen(buffer));
    WritingError();
}
void Client :: ReadMsg()
{
    bzero(buffer, 256);
    n = read(sockfd, buffer, 255);
    ReadingError();
    std :: cout << buffer << std :: endl;
}

void Client :: Run()
{
    HostHoding();
    EstablishedSocket();
    GetHostName();
    setServeraddr();
    Connect();
    GetMsg();
    ReadMsg();
}
int main(int argc, char **argv)
{
    Client c1(argc, argv);
    c1.Run();
    return 0;
}

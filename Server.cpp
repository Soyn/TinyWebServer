#include "Server_cpp.h"
#include <cerrno>
#include<cstdio>

/**
* This is a simple web server by c++.
* Created by Sony. 15/09/15.
**/
void Server :: error(const char* msg)
{
    std :: perror(msg);
    exit(1);
}

///constructor
Server :: Server(int argc, char **argv)
{
    std ::cout << "Constructor" << std:: endl;
    std ::cout << argc << std :: endl;
    std :: cout << *argv << std :: endl;
    this -> argc = argc;
    this -> argv = argv;
}
///desconstructor
Server:: ~Server()
{
    std :: cout <<"Desconstructor" << std :: endl;
     close(newsockfd);
     close(sockfd);
}

void Server :: PortError()
{
    if(argc < 2){
        std :: cerr << "Error, no port provided\n" << std :: endl;
        exit(1);
        }
}

void Server :: OpenSockError()
{
    if(sockfd < 0)
        error("ERROR opening socket");
}

void Server :: BindError()
{
    if(bind(sockfd, (sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");
}

void Server :: AcceptError()
{
    if( newsockfd < 0)
        error("ERROR on accept");
}

void Server :: ReadingError()
{
    if(n < 0)
        error("ERROR reading from socket");
}

void Server :: WritingError()
{
    if( n < 0)
        error("ERROR writing to socket");
}

void Server :: CreateSocket()
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);    //create a socket
    OpenSockError();
}

void Server :: SetServerAdd()
{
    bzero((char*)&serv_addr, sizeof(serv_addr));
    portno = std::atoi(argv[1]);    //convert the port number from string of digits to an interger
    serv_addr.sin_family = AF_INET; //must be AF_INET which contain a code for the address family
    serv_addr.sin_addr.s_addr = INADDR_ANY; //INADDR_ANY will get the IP address on which server runs.
    serv_addr.sin_port = htons(portno); //convert the port number in host byte order to network order
    BindError();
    listen(sockfd, 5);
}

void Server :: EstablishConnect()
{
    clilen = sizeof(cli_addr);
    newsockfd = accept( sockfd, ( sockaddr*) &cli_addr, &clilen);
    AcceptError();
}

void Server:: ReadMessage()
{
    bzero(buffer,256);
    n = read( newsockfd, buffer, 255);
    ReadingError();
    std :: cout << "Here is the message: " << buffer << '\n';
}

void Server :: WriteMessage()
{
    n = write(newsockfd, "I get your message", 18);
    WritingError();
}

void Server :: Run()
{
    PortError();
    CreateSocket();
    SetServerAdd();
    EstablishConnect();
    ReadMessage();
    WriteMessage();
}

int main(int argc, char **argv)
{
    Server s1(argc, argv);
    s1.Run();
    return 0;
}

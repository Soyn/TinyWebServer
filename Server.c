#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

/**
* This is a simple server in the internet domain using TCP, the port number is passed as an argument.
* Created by Soyn.16/9/15.
**/
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    ///<var name = "sockfd">  file description, get from the socket system call</var name>
    ///<var name = "newsockfd">the file description, get from the accept system call </the socket description>
    ///<var name= "portnum"> portno stores the port number on which the server accepts connections</var name>
    ///<var name = "clilen"> the size of client address</var name>
    ///<var name = "buffer[256]">the server reads characters from the socket into this buffer</var name>
    ///<var name = "serv_addr">the address of the server</var name>
    ///<var name = "cli_addr">the address of the client which connects to the server</var name>

    int sockfd,newsockfd,portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;     //struct sockaddr_in is a structure containing an internet address, which is defined in netinet/in.h.
    int n;

    if ( argc < 2)
    {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM,0);  // created a socket, and returns  to sockfd.

    if( sockfd <0)
        error("ERROR opening socket");

    bzero((char*) &serv_addr, sizeof(serv_addr)); // initialize the serv_addr all to zero

    portno = atoi(argv[1]);                                                 //convert the port number from string of digits to an interger.

    serv_addr.sin_family = AF_INET;                             //must be AF_INET which contains a code  for the address family.
    serv_addr.sin_addr.s_addr = INADDR_ANY;            //INADDR_ANY will get the IP address on which server runs.
    serv_addr.sin_port = htons(portno);                     //convent the port number in host byte order to network byte order.

    if( bind(sockfd, ( struct sockaddr*)&serv_addr, sizeof( serv_addr)) < 0) // bind system call will bind a socket to an address,
                                                                                                                                        //ps: the second parament of bind() takes a point to struct sockaddr, and we pass the struct sockaddr_in, so we need case this to the correct type.
        error("ERROR on binding");

    listen(sockfd, 5);  //listen() system call allows the process to listen on the socket for connection.

    clilen = sizeof(cli_addr);
    newsockfd = accept( sockfd, ( struct sockaddr*) &cli_addr, &clilen);

    if( newsockfd < 0)
        error("Error on accept");

    bzero(buffer, 256);
    n = read(newsockfd, buffer, 255);

    if( n < 0)
        error("ERROR reading from socket");

    printf("Here is the message: %s\n", buffer);
    n = write(newsockfd, "I get your message", 18);

    if( n < 0)
        error("ERROR writing to socket");

    close(newsockfd);
    close(sockfd);
    return 0;

}

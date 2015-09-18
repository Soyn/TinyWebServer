#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
 #include <sys/socket.h>
 #include <netinet/in.h>
#include <netdb.h>

///
/// <summary>a system call fails, this function will be called.</summary>
/// <para name = "msg"> the message about the error. </para name>
///


void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    ///
    /// <var name = "socked"> stores the value returned by socket system. call</variable name>
    /// <var name = "portno">stores the port number where the server accepts connections.</var name>
    /// <var name = "n">n is the return value for read() and write()</var name>
    ///
    int sockfd,portno,n;
    struct sockaddr_in serv_addr; // the client read characters from the server address.
    struct hostent *server;      // a pointer to a structure of type hostent.
    /**
      struct hostent
      {
        char *h_name;        //official name of host
        char **h_aliases;   //alias list
        int h_addrtype;      // host address type
        int h_length;           //length of address
        char **h_addr_list; //list of address from name server
        #define h_addr h_addr_list[0]  //address, for backward compatiblity
      };
    **/

    char buffer[256];            // the server reads (writes) the characters from the socket into the buffer.

    if(argc < 3)
    {
        fprintf(stderr,"usage %s hostname port\n", argv[0]);
        exit(0);
    }
    portno = atoi(argv[2]);         //convert the port number from string of digits to an interger
    sockfd = socket(AF_INET,SOCK_STREAM,0); //use internet domain, and a stream socket

    if(sockfd < 0)
        error("ERROR opening socket.");

    server = gethostbyname(argv[1]);   //   the argv[1] contains the name of a host on the Internet,this function returns a pointer to a hostent containing information about that host

    if(server == NULL)
    {
        fprintf(stderr, "no such host\n");
        exit(0);
    }

    bzero((char*)&serv_addr, sizeof(serv_addr)); // initilize the serv_addr  to 0

    serv_addr.sin_family = AF_INET;                             //must be symbolic constant

    bcopy((char*)server -> h_addr, (char*)&serv_addr.sin_addr.s_addr,server -> h_length);     // copy length bytes from 'server-> h_addr' to 'serv_addr.sin_addr.s_addr'

    serv_addr.sin_port = htons(portno);                     //convent host byte order to network byte order

    if(connect(sockfd,(struct sockaddr_in *)&serv_addr,sizeof(serv_addr)) < 0)  // connect function is called to establish a connection to the server
        error("ERROR connecting");

    printf("Please enter the message: ");

    bzero(buffer,256);
    fgets(buffer,255,stdin);

    n = write(sockfd, buffer,strlen(buffer));

    if(n < 0)
        error("Error writing to socket");

    bzero(buffer,256);
    n = read(sockfd,buffer,255);

    if(n < 0)
        error("ERROR reading from socket");
    printf("%s\n",buffer);
    close(sockfd);
    return 0;
}

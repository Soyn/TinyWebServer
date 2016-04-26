#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED
/**********************************************
* @Author: Soyn
* @Brief: A simple example client for tcp socket
* @CreatedTime: 15/09/15
* @Soyn: Refactor the code in 25/4/16
***********************************************/
#include "error_handle_for_client.h"
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <cerrno>

#include <iostream>
#include <string>
#include <memory>
#define BUFFERSIZE 256


class Client{
public:
    Client(int argc, char **argv);
    ~Client();
    //
    // Display the error message
    void ErrorMessageDisplay(const std :: string message);
    void HostHoding();
    //
    // Create client socket
    void CreateClientSocket();
    //
    // @Brief: Get host name
    void GetHostName();
    //
    // Set the socket
    void SetClientSocket();
    //
    // Establish connection with server
    void EstablishConnection();
    //
    // Write message to server
    void WriteMessageToConnection();
    //
    // @Brief: Read message from connection
    void ReadMessageFromConnection();
    //
    // Wrap all the procedure together
    void Run();
private:
    int client_socket_file_description_, server_port_number_,
    argument_counts_;
    sockaddr_in server_address_;
    hostent *server_host_entry_;
    char buffer[BUFFERSIZE], **argument_values_;
    ClientErrorHandler error_handler_;
private:
};


#endif // CLIENT_H_INCLUDED

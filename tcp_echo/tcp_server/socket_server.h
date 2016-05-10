#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

/****************************************************
* @Author: Soyn
* @Brief: Implement the procedure to communicate with
* client using socket.
* @CreatedTime:25/9/15.
* @Soyn: Refact the code(29/3/16.)
****************************************************/
#include "error_handler_for_server.h"
#include "signal_handler.h"

#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <signal.h>
#include <arpa/inet.h>

#include <iostream>
#include <string>

class Server{
public:
    //
    // @Brief: The constructor takes argc and argv.
    // @Para name argc: argument counts.
    // @Para name argv: argument value.
    Server(int argc, char **argv) : argc_(argc), argv_(argv),
                                        error_handler_(argc_){}
    ~Server(){close(listen_socket_file_description_);}

    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    //
    // @Brief: Create a socket.
    void CreateSocket();
    //
    // @Brief: Set the server address and others.
    void SetServerAddress();
    //
    // @Brief: Binding the specified socket with server.
    void BindSocketWithServer();
    //
    // @Brief: Establish the connect with client, allow
    // one or more connections.
    void EstablishConnect();

    //
    // @Brief: Read and write the message and display on the screen.
    void DisplayMessageFromClient();
    //
    // @Brief: Package all the procedures.
    void Run();

private:
    int listen_socket_file_description_, connect_socket_file_description_;
    int port_number_;
    int argc_;
    int pid_;
    socklen_t client_length_;
    char **argv_;
    sockaddr_in server_address_, client_address_;

    ErrorHandler error_handler_;  // The error handler to handle error.

    SignalHandler signal_handler_;
};


#endif // SERVER_H_INCLUDED

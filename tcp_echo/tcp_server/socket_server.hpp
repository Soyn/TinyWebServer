#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

/****************************************************
* @Author: Soyn
* @Brief: Implement the procedure to communicate with
* client using socket.
* @CreatedTime:25/9/15.
* @Soyn: Refact the code(29/3/16.)
****************************************************/
#include "error_handler_for_server.hpp"
#include "signal_handler.hpp"

#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>

#include <iostream>
#include <string>

class Server{
public:
    //
    // @Brief: The constructor takes argc and argv.
    // @Para name argc: argument counts.
    // @Para name argv: argument value.
    Server(int argc, char **argv) : argument_counts_(argc),
        argument_values_(argv), continue_or_not_(false),
        error_handler_(argument_counts_){}
    ~Server(){close(listen_socket_file_descriptor_);}

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
    void EstablishConnection();

    //
    // @Brief: Read and write the message and display on the screen.
    void DisplayMessageFromClient(size_t index);
    //
    // @Brief: Package all the procedures.
    void Run();

private:
    int listen_socket_file_descriptor_, connect_socket_file_descriptor_,
        maximum_file_descriptor_, socket_file_descriptor_;
    int port_number_, argument_counts_;
    int pid_, max_index_of_client_array_, number_ready_;
    int client_[FD_SETSIZE];
    char **argument_values_;
    enum {BUFSIZE = 1024, MAXLINE = 1024};
    bool continue_or_not_;

    fd_set read_set_, all_set_;

    socklen_t client_length_;
    sockaddr_in server_address_, client_address_;

    ErrorHandler error_handler_;  // The error handler to handle error.

    SignalHandler signal_handler_;  // the signal handler for server

private:
    //
    // @Brief: initialize the client connection
    void InitClientConnection();

    //
    // @Brief: Ready for select() call
    void ReadForSelect();

};


#endif // SERVER_H_INCLUDED

#include "server.h"
#define BUFSIZE 1024


/**
* This is a simple web server by c++.
* Created by Soyn. 15/09/15.
**/

//
// @Brief: Check port open or not.

void Server :: CheckPort()
{
    error_handler_.CheckPortOpenOrNot();
}

//
// @Brief: Create a socket for communicate with client.
void Server :: CreateSocket()
{
    socket_file_description_ = socket(AF_INET, SOCK_STREAM, 0);
    error_handler_.CheckSocketCreatedOrNot(socket_file_description_);
}

//
// @Brief: Set the server address, port number
void Server :: SetServerAddress()
{
    bzero((char*)&server_address_, sizeof(server_address_));
    // convert the port number from string of digits to an interger.
    port_number_ = atoi(argv_[1]);

     // must be AF_INET which contain a code for the address family.
    server_address_.sin_family = AF_INET;

    // INADDR_ANY will get the IP address on which server runs.
    server_address_.sin_addr.s_addr = INADDR_ANY;

    // convert the port numberin host byte order to network order.
    server_address_.sin_port = htons(port_number_);
}

//
// @Brief: Bind the socket with server.
void Server :: BindSocketWithServer()
{
    int bind_flag = bind(socket_file_description_, (sockaddr*)
                        (&server_address_), sizeof(server_address_));
    error_handler_.CheckBindOrNot(bind_flag);
    listen(socket_file_description_, 5);
}

//
// @Brief: Establish connect with client.
void Server :: EstablishConnect()
{
    client_length_ = sizeof(client_address_);
    while(1)
    {
        //establish the connection
        new_socket_file_description_ = accept(socket_file_description_,
                            (sockaddr*) &client_address_, &client_length_);
        error_handler_.CheckAcceptOrNot(new_socket_file_description_);

        pid_ = fork();      //create a new process to handle this connection
        if(pid_ < 0)
           error_handler_.ErrorMessageDisplay("Error on fork");
        if(pid_ == 0)
        {
            close(socket_file_description_);
            DisplayMessageFromClient();
            exit(0);  // the process exits
        }
        else
             // the parent closes the new socket file description
            close(new_socket_file_description_);
    }
}

//
// @Brief: Read and write message, and display the message.
void Server :: DisplayMessageFromClient()
{
    int n;
    char buffer[BUFSIZE];

    bzero(buffer,BUFSIZE);
    n = read(new_socket_file_description_,buffer,BUFSIZE - 1);
    if(n < 0)
        error_handler_.ErrorMessageDisplay("ERROR reading from socket");
    std :: cout << "Here is the message: " << buffer << std :: endl;
    n = write(new_socket_file_description_,"I get your message", 18);

    if(n < 0)
        error_handler_.ErrorMessageDisplay("Error writing to socket");
}


//
// @Brief: To package all the procedures.
void Server :: Run()
{
    CheckPort();
    CreateSocket();
    SetServerAddress();
    BindSocketWithServer();
    EstablishConnect();
}

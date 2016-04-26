/**************************************
* @Author: Soyn
* @Brief: Simple example for tcp socket
* @CreatedTime: 15/9/15
* @Soyn: Refactor the code in 25/4/16.
**************************************/

#include "socket_client.h"
//
// @Brief: The constructor takes command paraments
Client :: Client(int argument_counts, char **argument_values) :
    argument_counts_(argument_counts), argument_values_(argument_values),
    error_handler_(argument_counts_, argument_values_){}

//
// @Brief: The deconstructor
Client :: ~Client()
{
    close(client_socket_file_description_);
}

//
// @Brief: Create the client socket
void Client :: CreateClientSocket()
{
    server_port_number_ = std :: atoi(argument_values_[2]);
    client_socket_file_description_ = socket(
                                                    AF_INET, SOCK_STREAM, 0);

    error_handler_.CheckSocketCreatedOrNot(
                                client_socket_file_description_);
}

//
// @Brief: Get the host name
void Client :: GetHostName()
{
    server_host_entry_ = gethostbyname(argument_values_[1]);
    error_handler_.HostNameError(server_host_entry_);
}


//
// @Brief: Set client socket
void Client :: SetClientSocket()
{
    GetHostName();

    bzero((char *) &server_address_, sizeof(server_address_));
    server_address_.sin_family = AF_INET;
    bcopy((char *)server_host_entry_->h_addr, (char *)
          &server_address_.sin_addr.s_addr, server_host_entry_->h_length);
    server_address_.sin_port = htons(server_port_number_);
}

//
// @Brief: establish the connection with server
void Client :: EstablishConnection()
{
    int connection_status = connect(client_socket_file_description_,
          (sockaddr*)&server_address_, sizeof(server_address_));
    error_handler_.CheckConnection(connection_status);
}

//
// @Brief: write the message to connection
void Client :: WriteMessageToConnection()
{
    std :: cout << "Please Enter Your Message: " << std :: endl;
    bzero(buffer, BUFFERSIZE);
    fgets(buffer, BUFFERSIZE - 1, stdin);
    int writing_return_value = write(
                    client_socket_file_description_, buffer, BUFFERSIZE - 1);
    error_handler_.WritingError(writing_return_value);
}

//
// @Brief: read message from the connection
void Client :: ReadMessageFromConnection()
{

    bzero(buffer, BUFFERSIZE);
    int reading_return_value = read(client_socket_file_description_,
                            buffer, BUFFERSIZE - 1);
    error_handler_.ReadingError(reading_return_value);
    std :: cout << buffer << std :: endl;
}

//
// @Brief: Wrap all th procedures together
void Client :: Run()
{
    error_handler_.CheckHost();
    CreateClientSocket();
    SetClientSocket();
    EstablishConnection();
    WriteMessageToConnection();
    ReadMessageFromConnection();
}

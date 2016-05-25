/*********************************************
* @Author: Soyn
* @Brief: This is a simple web server by c++.
* @CreatedTime: 15/09/15
* @Refactor: By Soyn 3/5/16
*********************************************/

#include "socket_server.hpp"

//
// @Brief: Create a socket for communicate with client.
void Server :: CreateSocket()
{
    error_handler_.CheckPortOpenOrNot();
    listen_socket_file_descriptor_ = socket(AF_INET, SOCK_STREAM, 0);
    error_handler_.CheckSocketCreatedOrNot(listen_socket_file_descriptor_);
}

//
// @Brief: Set the server address, port number
void Server :: SetServerAddress()
{
    bzero((char*)&server_address_, sizeof(server_address_));
    // convert the port number from string of digits to an integer.
    port_number_ = atoi(argument_values_[1]);

     // must be AF_INET which contain a code for the address family.
    server_address_.sin_family = AF_INET;

    // INADDR_ANY will get the IP address on which server runs.
    server_address_.sin_addr.s_addr = INADDR_ANY;

    // convert the port number in host byte order to network order.
    server_address_.sin_port = htons(port_number_);
}

//
// @Brief: Bind the socket with server.
void Server :: BindSocketWithServer()
{
    int bind_flag = bind(listen_socket_file_descriptor_, (sockaddr*)
                        (&server_address_), sizeof(server_address_));
    error_handler_.CheckBindOrNot(bind_flag);
    listen(listen_socket_file_descriptor_, 64);
    InitClientConnection();
    signal_handler_.Signal(SIGCHLD, SignalChild);
}

//
// @Brief: Establish connect with client.
// @Note: Single process handle connection using select()
void Server :: EstablishConnection()
{
    client_length_ = sizeof(client_address_);
    while(1)
    {
        ReadForSelect();  // get ready for the connection
        for(auto i = 0; i < max_index_of_client_array_; ++i){  // check all clients for data
            if((socket_file_descriptor_ = client_[i]) < 0){
                continue;
            }

            if(FD_ISSET(socket_file_descriptor_, &read_set_)){
                DisplayMessageFromClient(i);
            }
            if(--number_ready_ <= 0)
                break;
        }
    }
}

//
// @Brief: Read and write message, and display the message.
void Server :: DisplayMessageFromClient(size_t index)
{
    int number_bytes;
    char buffer[Server::BUFSIZE];

    bzero(buffer,Server::BUFSIZE);
    number_bytes = read(socket_file_descriptor_,buffer,Server::BUFSIZE - 1);
    std::cout << buffer << std::endl;
    if(number_bytes == 0){  // connection closed by client
        close(socket_file_descriptor_);
        FD_CLR(socket_file_descriptor_, &all_set_);
        client_[index] = -1;
    }else{
        std :: cout << "Here is the message:\n" << buffer << std :: endl;
        write(socket_file_descriptor_, buffer, Server::MAXLINE);
    }
}

//
// @Brief: initialize the client connection array
// @Note: private method
void Server::InitClientConnection()
{
    maximum_file_descriptor_ = listen_socket_file_descriptor_;
    max_index_of_client_array_ = -1;  // no connection at begin

    // assign -1 to each element in client array,
    // implies there is no connection client
    for(auto i = 0; i < FD_SETSIZE; ++i){
        client_[i] = -1;
    }
    FD_ZERO(&all_set_);
    FD_SET(listen_socket_file_descriptor_, &all_set_);
}

//
// @Brief: Ready for select() call
void Server::ReadForSelect()
{
    int i;
    read_set_ = all_set_;
    number_ready_ = select(maximum_file_descriptor_ + 1, &read_set_,
                            nullptr, nullptr, nullptr);
    if(FD_ISSET(listen_socket_file_descriptor_, &read_set_)){  // new client connection
        connect_socket_file_descriptor_ = accept(
            listen_socket_file_descriptor_, (struct sockaddr*)
                &client_address_, &client_length_);
        // set first position which is negative
        for(i = 0; i < FD_SETSIZE; ++i){
            if(client_[i] < 0){
                client_[i] = connect_socket_file_descriptor_;
                break;
            }
        }

        if(i == FD_SETSIZE){
            error_handler_.ErrorMessageDisplay("too many clients");
        }
        FD_SET(connect_socket_file_descriptor_, &all_set_);

        if(connect_socket_file_descriptor_ > maximum_file_descriptor_){
            // for select
            maximum_file_descriptor_ = connect_socket_file_descriptor_;
        }

        if(i > max_index_of_client_array_){
            max_index_of_client_array_ = i;
        }

        if(--number_ready_ <= 0)  // no more readable descriptor
            continue_or_not_ = true;
    }
}
//
// @Brief: To package all the procedures.
void Server :: Run()
{
    CreateSocket();
    SetServerAddress();
    BindSocketWithServer();
    EstablishConnection();
}

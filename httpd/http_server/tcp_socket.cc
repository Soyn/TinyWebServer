/***********************************
* @Author: Soyn
* @Brief: Tcp socket for http server
* @CreatedTime: 1/11/15
* @Refactor: Soyn at 5/5/16
************************************/

#include "tcp_socket.hpp"
//
// @Brief: Do some necessary work before creating socket
void TcpSocket::ReadyWorkForCreateSocket()
{
    logger_.Logging(Logger::LOG, "Yweb starting ", argument_values_[1], getpid());
}
//
// @Brief: Creating a listen socket
void TcpSocket::CreateSocket()
{
    ReadyWorkForCreateSocket();
    bzero(&server_address_, sizeof(server_address_));
    port_number_ = atoi(argument_values_[1]);

    if(port_number_ < 0 || port_number_ > 60000){

        logger_.Logging(Logger::ERROR, "Invalid port number (try 1~60000)",
                        argument_values_[1], 0);
    }

    int option_value = 1;
    listen_socket_file_descriptor_ = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(listen_socket_file_descriptor_, SOL_SOCKET, SO_REUSEADDR,
        (char*)&option_value, sizeof(option_value));  // reuse the address

    if(listen_socket_file_descriptor_ < 0){
        logger_.Logging(Logger::ERROR, "System call", "socket", 0);
    }

    server_address_.sin_family = AF_INET;
    server_address_.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address_.sin_port = htons(port_number_);
    int bind_flag = bind(listen_socket_file_descriptor_, (struct sockaddr*)
            &server_address_, sizeof(server_address_));

    if(bind_flag < 0){
        logger_.Logging(Logger::ERROR, "System call", "bind", 0);
    }

    int listen_flag = listen(listen_socket_file_descriptor_, 64);

    if(listen_flag < 0){
        logger_.Logging(Logger::ERROR, "System call", "listen", 0);
    }

    client_length_ = sizeof(client_address_);
    // listening
    accept(listen_socket_file_descriptor_, (struct sockaddr*) &client_address_,
           &client_length_);
}

//
// @Brief: Get the port number
int TcpSocket::GetPortNumber() const
{
    return port_number_;
}

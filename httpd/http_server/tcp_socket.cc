/***********************************
* @Author: Soyn
* @Brief: Tcp socket for http server
* @CreatedTime: 1/11/15
* @Refactor: Soyn at 5/5/16
************************************/

#include "tcp_socket.hpp"
//
// @Brief: Creating a listen socket
void TcpSocket :: CreateSocket()
{
    bzero(&server_address_, sizeof(server_address_));
    port_number_ = atoi(argument_values_[1]);

    if(port_number_ < 0 || port_number_ > 60000){
        logger_.Logging(Logger :: ERROR, "Invalid port number (try 1~60000)",
                        argument_values_[1], 0);
    }

    listen_socket_file_description_ = socket(AF_INET, SOCK_DGRAM, 0);

    if(listen_socket_file_description_ < 0){
        logger_.Logging(Logger :: ERROR, "System call", "socket", 0);
    }

    server_address_.sin_family = AF_INET;
    server_address_.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address_.sin_port = htons(port_number_);

    int bind_flag = bind(listen_socket_file_description_, (struct sockaddr*)&server_address_,
          sizeof(server_address_));

    if(bind_flag < 0){
        logger_.Logging(Logger :: ERROR, "System call", "bind", 0);
    }

    int listen_flag = listen(listen_socket_file_description_, 64);

    if(listen_flag < 0){
        logger_.Logging(Logger :: ERROR, "System call", "listen", 0);
    }
}


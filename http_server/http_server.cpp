/**********************************
* @Author: Soyn
* @Brief: the simple http server
* @CreatedTime: 1/11/15.
* @RefactorTime: Soyn at 30/4/16
 *********************************/

#include "http_server.h"
#include <iostream>

const int Logger :: Error = 42, Log = 44, Forbidden = 403,
 NotFound = 404, BufferSize = 8096;
//
// @Brief: Open the server
// @Note:
// This part is to open the server for connection.
void HttpServer :: OpenServer()
{
    InitializeServer();
}

//
// @Brief: Initialize the server including checking the error
void HttpServer :: InitializeServer()
{
    error_handler_.CheckRequestSupportedVaildOrNot();
    error_handler_.CheckRequestDirectoryValidOrNot();
    error_handler_.CheckChangeDirectoryValidOrNot();
    CreateSocket();
}

//
// @Brief: create the predictor function
bool HttpServer :: IsDelimiter(const char &chr)
{
    return (chr == '\r' || chr == '\n');
}

//
// @Brief: Handle the request from client
void HttpServer :: HandleRequest(int connected_socket_file_description,
                                 int hit)
{
    std :: string buffer;

    //
    // @Brief: read from socket
    auto ret = read(connected_socket_file_description, buffer.c_str(), BufferSize);
    if(ret == 0 || ret == -1){
        logger_.Logging(Forbidden, "failed to read browser request");
    }

    if(ret < -1 || ret > BufferSize){
        buffer.clear();
    }

    std :: replace_if(buffer.begin(), buffer.end(), IsDelimiter(), '*');

    logger_.Logging(Log, "request", buffer, hit);

    std :: string http_method = buffer.substr(0, 3);
    if(request == "GET" || request == "get"){
        logger_.Logging(Forbidden, "Only Simple GET operation supported", buffer,
                        connected_socket_file_description);
    }

    std :: size_t found = buffer.find("..");
    if(found != std :: string :: npos){
        logger_.Logging(Forbidden, "Parent directory (..) path names not\
supported", buffer, connected_socket_file_description);
    }

    http_method = buffer.substr(0, 5);
    if(http_method == "Get /" || http_method == "get /"){
        buffer.replace(0, 5, "GET /index.html");
    }

    bool supported_file_type = false;
    std :: string request_file_type;
    for(int i = 0; ErrorHandler ::
        supported_file_type_collections_[i].file_extension_; ++i){
        if(buffer.find(
                supported_file_type_collections_[i].file_extension_) != npos){
            supported_file_type = true;

            request_file_type =
                supported_file_type_collections[i].file_extension_;
        }
    }

    if(SupportedFileType){
        logger_.Logging(Forbidden, "file extension type not supported", buffer,
                        connected_socket_file_description);
    }
    std :: ifstream request_file_stream(buffer.substr(5));
    auto start_position_of_file = request_file_stream.tellg();

    if(request_file_stream.is_open()){
        logger_.Logging(NotFound, "failed to open file", buffer.substr(5),
                        connected_socket_file_description);
    }
    logger_.Logging(Log, "SEND", buffer.substr(5), hit);

    auto request_file_stream.seekg(0, ios :: end);
    auto end_position_of_file = request_file_stream.tellg();
    long int length_of_request_file = end_position_of_file -
                                            start_position_of_file;

    request_file_stream.seekg(0, ios :: beg);

    std :: ostringstream writting_buffer_stream(buffer);

    writting_buffer_stream << "HTTP/1.1 200 OK\nServer: YWeb " <<
    ErrorHandler :: version_ << "\nContent-Length: " << length_of_request_file
    << "\nConnection: close\nContent-Type: " << request_file_type << "\n\n";
    writting_buffer_stream.close();

    write(connected_socket_file_description, buffer.c_str(), buffer.length());
    int file_description = open(buffer.substr(5), O_RDONLY);
    while(ret = read(file_description, buffer, buffer.length()) > 0){
        write(connected_socket_file_description, buffer, ret);
    }

    sleep(1);
    close(connected_socket_file_description);
    exit(1);

}

//
// @Brief: Send the response to client

void HttpServer :: SendResponse()
{
    int connected_socket_file_description;
    for(int hit = 1; ; ++hit){
        int connected_client_length = sizeof(client_address_);
        if((connected_socket_file_description = accept(
            listen_socket_file_description_, (struct sockaddr*)&client_address_,
            &connected_client_length)) < 0){
            logger_.Logging(Error, "system call", "accept", 0);
            }
            if(int pid = fork() < 0){
                logger_.Logging(Error, "system call", "fork", 0);
            }else{
                if(pid == 0){
                    close(listen_connected_file_description_);
                    HandleRequest(conncted_socket_file_description, hit);
                }else{
                    close(connected_socket_file_description);
                }
            }
    }
}



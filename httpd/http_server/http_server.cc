/**********************************
* @Author: Soyn
* @Brief: the simple http server
* @CreatedTime: 1/11/15.
* @RefactorTime: Soyn at 30/4/16
 *********************************/

#include "http_server.hpp"
#include <iostream>

const int HttpServer :: BufferSize = 8096;
//
// @Brief: the predictor function
bool IsDelimiter(const char &chr)
{
    return (chr == '\r' || chr == '\n');
}

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
    error_handler_.CheckRequestSupportedValidOrNot();
    error_handler_.CheckRequestDirectoryValidOrNot();
    error_handler_.CheckChangeDirectoryValidOrNot();
    CreateSocket();
}

//
// @Brief: Handle the request from client
void HttpServer :: HandleRequest(int connected_socket_file_description,
                                 int hit)
{
    std :: string buffer;

    //
    // @Brief: read from socket
    auto ret = read(connected_socket_file_description, const_cast<char*>(buffer.c_str()),
                    BufferSize);

    if(ret == 0 || ret == -1){
        logger_.Logging(Logger::FORBIDDEN, "failed to read browser request", " ",
                        connected_socket_file_description_);
    }

    if(ret < -1 || ret > BufferSize){
        buffer.clear();
    }

    std :: replace_if(buffer.begin(), buffer.end(), IsDelimiter, '*');

    logger_.Logging(Logger::LOG, "request", buffer, hit);

    std :: string http_method = buffer.substr(0, 3);
    if(http_method == "GET" || http_method == "get"){
        logger_.Logging(Logger::FORBIDDEN, "Only Simple GET operation supported", buffer,
                        connected_socket_file_description);
    }

    std :: size_t found = buffer.find("..");
    if(found != std :: string :: npos){
        logger_.Logging(Logger::FORBIDDEN, "Parent directory (..) path names not\
supported", buffer, connected_socket_file_description);
    }

    http_method = buffer.substr(0, 5);
    if(http_method == "Get /" || http_method == "get /"){
        buffer.replace(0, 5, "GET /index.html");
    }

    bool supported_file_type = false;
    std :: string request_file_type;
    for(int i = 0; ErrorHandler ::
        supported_file_type_collections_[i].file_extension_ != "0"; ++i){
        if(buffer.find(ErrorHandler ::
                    supported_file_type_collections_[i].file_extension_) !=
           std :: string :: npos){

            supported_file_type = true;

            request_file_type =
                ErrorHandler::
                    supported_file_type_collections_[i].file_extension_;
        }
    }

    if(!supported_file_type){
        logger_.Logging(Logger::FORBIDDEN, "file extension type not supported", buffer,
                        connected_socket_file_description);
    }
    std :: ifstream request_file_stream(buffer.substr(5));
    auto start_position_of_file = request_file_stream.tellg();

    if(request_file_stream.is_open()){
        logger_.Logging(Logger::NOTFOUND, "failed to open file", buffer.substr(5),
                        connected_socket_file_description);
    }
    logger_.Logging(Logger::LOG, "SEND", buffer.substr(5), hit);

    request_file_stream.seekg(0, request_file_stream.end);
    auto end_position_of_file = request_file_stream.tellg();
    long int length_of_request_file = end_position_of_file -
                                            start_position_of_file;

    request_file_stream.seekg(0, request_file_stream.beg);

    std :: ostringstream writting_buffer_stream(buffer);

    writting_buffer_stream << "HTTP/1.1 200 OK\nServer: YWeb " <<
    ErrorHandler :: version_ << "\nContent-Length: " << length_of_request_file
    << "\nConnection: close\nContent-Type: " << request_file_type << "\n\n";

    write(connected_socket_file_description, const_cast<char*>(buffer.c_str()),
           buffer.length());
    int file_description = open(buffer.substr(5).c_str(), O_RDONLY);
    while((ret = read(file_description, const_cast<char*>(buffer.c_str()),
                      buffer.length())) > 0){
        write(connected_socket_file_description, buffer.c_str(), ret);
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
        socklen_t connected_client_length = sizeof(client_address_);
        if((connected_socket_file_description = accept(
            listen_socket_file_description_, (struct sockaddr*)&client_address_,
            &connected_client_length)) < 0){
            logger_.Logging(Logger::ERROR, "system call", "accept", 0);
            }
            if(int pid = fork() < 0){
                logger_.Logging(Logger::ERROR, "system call", "fork", 0);
            }else{
                if(pid == 0){
                    close(connected_socket_file_description);
                    HandleRequest(connected_socket_file_description, hit);
                }else{
                    close(connected_socket_file_description);
                }
            }
    }
}


//
// @Brief: Package all the procedure

void HttpServer :: Run()
{
    OpenServer();
    InitializeServer();
    SendResponse();
}


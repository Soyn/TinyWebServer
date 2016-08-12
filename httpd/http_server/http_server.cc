/**********************************
* @Author: Soyn
* @Brief: the simple http server
* @CreatedTime: 1/11/15.
* @RefactorTime: Soyn at 30/4/16
 *********************************/

#include "http_server.hpp"
#include <iostream>

const int HttpServer::BUFFERSIZE = 8096;
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
void HttpServer::OpenServer()
{
    InitializeServer();
}

//
// @Brief: Initialize the server including checking the error
void HttpServer::InitializeServer()
{
    error_handler_.CheckRequestSupportedOrNot();
    error_handler_.CheckRequestDirectoryValidOrNot();
    error_handler_.CheckChangeDirectoryValidOrNot();
    CreateSocket();
}

//
// @Brief: Get the request from client
void HttpServer::GetRequest(const int& connected_socket_file_descriptor,
                            int hit)
{
    char copy_of_buffer[BUFFERSIZE];
    auto bytes_counts_from_socket = read(connected_socket_file_descriptor,
                    copy_of_buffer, BUFFERSIZE);
    buffer_ = copy_of_buffer;

    std::replace_if(buffer_.begin(), buffer_.end(), IsDelimiter, '*');
    if(bytes_counts_from_socket > 0)
        logger_.Logging(Logger::LOG, "request: ", buffer_, hit);
    if((bytes_counts_from_socket == 0) || (bytes_counts_from_socket == -1)){
        logger_.Logging(Logger::FORBIDDEN, "failed to read browser request",
                        " ", connected_socket_file_descriptor);
    }

    if(bytes_counts_from_socket < -1 || bytes_counts_from_socket > BUFFERSIZE){
        buffer_.clear();
    }

}
//
// @Brief: Handle the request from client
void HttpServer::HandleRequest(const int& connected_socket_file_descriptor,int hit)
{
    std::string http_method = buffer_.substr(0, 3);

    if(http_method == "GET" && http_method == "get"){
        logger_.Logging(Logger::FORBIDDEN, "Only Simple GET operation supported", buffer_,
                        connected_socket_file_descriptor);
    }

    std::size_t found = buffer_.find("..");
    if(found != std::string::npos){
        logger_.Logging(Logger::FORBIDDEN, "Parent directory (..) path names not\
supported", buffer_, connected_socket_file_descriptor);
    }

    GetTheRequestFileName();
    bool supported_file_type = false;

    auto iter = SupportFileType.find(request_file_type_);
    if(iter != SupportFileType.end()){
        supported_file_type = true;
    }
    if(!supported_file_type){
        logger_.Logging(Logger::FORBIDDEN, "file extension type not supported", buffer_,
                        connected_socket_file_descriptor);
    }
    request_file_type_ = SupportFileType[request_file_type_];
}

//
// @Brief: Get the resource file name
// @Note: Private method
void HttpServer::GetTheRequestFileName()
{
    unsigned int i = 4;
    while(i < buffer_.size() && buffer_[i] != ' '){
        ++i;
    }
    if(i > 5){
        request_resource_file_name_ = buffer_.substr(5, i - 5);
        for(i = 0; i < request_resource_file_name_.size() ; ++i){
            if(request_resource_file_name_[i] == '.'){
                break;
            }
        }
        request_file_type_ = request_resource_file_name_.substr(i + 1,
            std::string::npos);
    }else{
        buffer_.replace(0, 5, "GET /index.html");
        request_file_type_ = "html";
        request_resource_file_name_ = "index.html";
    }
}

//
//
// @Brief: Get the http head information
// @Note: Private member method
void HttpServer::GetHttpHeadInfo(const int& connected_socket_file_descriptor,
                             const int& hit)
{

    std::ifstream request_file_stream(request_resource_file_name_);

    auto start_position_of_file = request_file_stream.tellg();

    if(!request_file_stream.is_open()){
        logger_.Logging(Logger::NOTFOUND, "failed to open file",
        request_resource_file_name_,connected_socket_file_descriptor);
        }

        logger_.Logging(Logger::LOG, "SEND: \n", request_resource_file_name_,
                        hit);
        request_file_stream.seekg(0, request_file_stream.end);
        auto end_position_of_file = request_file_stream.tellg();
        length_of_request_file_ = end_position_of_file -
                                    start_position_of_file;

        request_file_stream.seekg(0, request_file_stream.beg);
}

//
// @Brief: Send http head
void HttpServer::SendHttpHead(const int& connected_socket_file_descriptor)
{
    buffer_.clear();
    std::string response_string("");

    std::ostringstream writting_buffer_stream(response_string);

    writting_buffer_stream << "HTTP/1.1 200 OK\nServer: YWeb "<<
        ErrorHandler::version_ << "\nContent-Length: " <<
        length_of_request_file_<< "\nConnection:close\nContent-Type: "
        << request_file_type_ << "\n\n";

    buffer_ = writting_buffer_stream.str();
    logger_.Logging(Logger::LOG, "Header: \n", buffer_, 2);

    write(connected_socket_file_descriptor, const_cast<char*>(buffer_.c_str()),
            buffer_.length());
}

//
// @Brief: Send request file to client
void HttpServer::SendRequestFile(const int& connected_socket_file_descriptor)
{
    int file_descriptor = open(request_resource_file_name_.c_str(), O_RDONLY);
    int bytes_counts_from_file = 0;

    while((bytes_counts_from_file = read(file_descriptor,
                const_cast<char*>(buffer_.c_str()),buffer_.length())) > 0){

                write(connected_socket_file_descriptor, buffer_.c_str(),
                    bytes_counts_from_file);
    }
}
//
// @Brief: Send the response to client
void HttpServer::SendResponse()
{
    int connected_socket_file_descriptor;
    int pid;
    for(int hit = 1; ; ++hit){
        socklen_t connected_client_length = sizeof(client_address_);
        if((connected_socket_file_descriptor = accept(
            listen_socket_file_descriptor_, (struct sockaddr*)&client_address_,
            &connected_client_length)) < 0){
            logger_.Logging(Logger::ERROR, "system call", "accept", 0);
            }
            if((pid = fork()) < 0){
                logger_.Logging(Logger::ERROR, "system call", "fork", 0);
            }else{
                if(pid == 0){
                    //close(connected_socket_file_descriptor);
                    // get and handle the request from client
                    GetRequest(connected_socket_file_descriptor, hit);
                    HandleRequest(connected_socket_file_descriptor, hit);
                    // get the http head info and send the info to client
                    GetHttpHeadInfo(connected_socket_file_descriptor,hit);
                    SendHttpHead(connected_socket_file_descriptor);
                    // send the request file
                    SendRequestFile(connected_socket_file_descriptor);

                    sleep(1);
                    close(connected_socket_file_descriptor);
                    exit(1);
                    }else{
                        close(connected_socket_file_descriptor);
                        }
            }
    }
}


//
// @Brief: Package all the procedure

void HttpServer::Run()
{
    OpenServer();
    SendResponse();
}


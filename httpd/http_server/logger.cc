/*********************************
* @Author: Soyn
* @Brief: The implementation of logger
* @CreatedTime: 30/4/16
*********************************/
#include "logger.hpp"

//
// @Brief: Get the current time
// @Note: Private method
void Logger::GetCurrentTime()
{
    time_t current_time = time(0);
    std::tm* now = localtime(&current_time);
    year_ = now->tm_year + 1900;
    month_ = now->tm_mon + 1;
    day_ = now->tm_mday;
    hour_ = now->tm_hour;
    minute_ = now->tm_min;
    second_ = now->tm_sec;
}
//
// @Brief: Record
void Logger::Logging(int type, const std :: string s1,
                const std::string s2, int socket_file_descriptor)
{
    std :: ofstream logger_file_stream("Yweb.log",std::ofstream::out |
                                        std::ofstream::app);
    GetCurrentTime();
    if(!logger_file_stream.is_open()){
        std::cout << "logger file opening failed!" << std::endl;
        return;
    }

    switch(type){
        case ERROR:{
            logger_file_stream << "ERROR: " << s1 + ":" + s2 + " " << "Errno = "
             << errno <<" pid = " << getpid() << " " << year_ << "/" << month_
             << "/" << day_ << " " << hour_ << ":" << minute_ << ":" << second_
             << "\n";
	if(logger_file_stream.bad()){
	    std::cout << "Writing to file failed" << std::endl;
	}
             break;
        }

        case FORBIDDEN: {
            std::string response_of_forbidden("HTTP/1.1 403 Forbidden\n\
Content-Length: 185\nConnection:close\nContent-Type:text/html\n\n<html>\
<head>\n<title>403 Forbidden</title>\n</head><body>\n<h1>Forbidden</h1>\n\
The request URL, file type or operation is not allowed on this simple static\
file web server\n</body></html>\n");
            write(socket_file_descriptor, response_of_forbidden.c_str(),
                  response_of_forbidden.length() + 1);
            logger_file_stream << "FORBIDDEN " << s1 + ":" + s2 << " " <<
            year_ << "/" << month_<< "/" << day_ << " " << hour_ << ":"
            << minute_ << ":" << second_ << "\n";
            break;
        }

        case NOTFOUND: {
            std::string response_of_not_found("HTTP/1.1 404 Not Found\n\
Content-Length: 136\nConnection:close\nContent-Type: text/html\n\n<html>\
<head>\n<title>404 Not Found</title>\n</head><body>\n<h1>Not Found</h1>\n\
The request URL was not found on this server.\n</body></html>\n");

            write(socket_file_descriptor, response_of_not_found.c_str(),
                response_of_not_found.length() + 1);
            logger_file_stream << "NOT FOUND: " << s1 + s2 << " " <<
            year_ << "/" << month_ << "/" << day_ << " " << hour_ << ":"
            << minute_ << ":" << second_ << "\n";
            break;
        }

        case LOG: {
            logger_file_stream << "INFO: " << s1 + " : "  + s2 + " : "
                << socket_file_descriptor << " " << year_ << "/" << month_
             << "/" << day_ << " " << hour_ << ":" << minute_ << ":" << second_
             << "\n";;
            break;
        }
    }
    logger_file_stream.close();
    if(type == ERROR || type == NOTFOUND || type == FORBIDDEN)
        exit(3);
}

void Logger::CleanLog()
{
    std::ofstream open_file_stream("Yweb.log",std::ofstream::out |
                                   std::ofstream::trunc);
    open_file_stream.close();
}

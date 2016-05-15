#include "logger.hpp"



void Logger :: Logging(int type, const std :: string s1,
                const std :: string s2, int socket_file_description)
{
    std :: ofstream logger_file_stream("Yweb.log");
    if(logger_file_stream)
        return;

    switch(type){
        case ERROR:{
            logger_file_stream << "ERROR: " << s1 + ":" + s2 + " " << "Errno = "
             << errno <<" pid = " << getpid() << "\n";
             break;
        }

        case FORBIDDEN: {
            std :: string response_of_forbidden("HTTP/1.1 403 Forbidden\n\
Content-Length: 185\nConnection:close\nContent-Type:text/html\n\n<html>\
<head>\n<title>403 Forbidden</title>\n</head><body>\n<h1>Forbidden</h1>\n\
The request URL, file type or operation is not allowed on this simple static\
file web server\n</body></html>\n");

            write(socket_file_description, response_of_forbidden.c_str(),
                  response_of_forbidden.length() + 1);
            logger_file_stream << "FORBIDDEN: " << s1 + ":" + s2 + "\n";
            break;
        }

        case NOTFOUND: {
            std :: string response_of_not_found("HTTP/1.1 404 Not Found\n\
Content-Length: 136\nConnection:close\nContent-Type: text/html\n\n<html>\
<head>\n<title>404 Not Found</title>\n</head><body>\n<h1>Not Found</h1>\n\
The request URL was not found on this server.\n</body></html>\n");

            write(socket_file_description, response_of_not_found.c_str(),
                response_of_not_found.length() + 1);
            logger_file_stream << "NOT FOUND: " << s1 + s2 + "\n";
            break;
        }

        case LOG: {
            logger_file_stream << "INFO: " << s1 + " : "  + s2 + " : "
                << socket_file_description;
            break;
        }
    }
    logger_file_stream.close();
    exit(3);

}

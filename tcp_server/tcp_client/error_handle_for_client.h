#ifndef ERROR_HANDLE_FOR_CLIENT_INCLUDED
#define ERROR_HANDLE_FOR_CLIENT_INCLUDED
/*****************************************
* @Author: Soyn
* @Brief: The error handler for client.
* @CreatedTime: 15/9/15
* @Soyn: Refactor the code in 25/4/16.
**/
#include <netdb.h>
class ClientErrorHandler{
public:
    ClientErrorHandler(int argument_counts, char **argument_values);
    ~ClientErrorHandler(){}
    //
    // @Brief: Check command arguments(i.e check the client host)
    void CheckHost();
    //
    // @Brief: Create the client socket
    void CreateClientSocket();
    void CheckSocketCreatedOrNot(const int &socket_file_description);
    //
    // @Brief: Check the connection
    void CheckConnection(const int &connection_status);
    //
    // @Check the writing succeed or not
    // @Para name: return_value => the value returns from write
    void WritingError(const int &writing_return_value);
    // @Brief: Check the host
    void HostNameError(const hostent *server_host_entry);
    void ReadingError(const int &connect_return_value);
private:
    //
    // private function for share and hiding
    void Error(const char *message);
    int argument_counts_;
    char **argument_values_;

};


#endif // ERROR_HANDLE_FOR_CLIENT_INCLUDED

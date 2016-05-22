#include "test_cases_header.hpp"
/*******************************
* @Author: Soyn
* @Brief: Test case for tcp socket
* @Details:
*     1. First compile the code
*     2. Then run the execute program(eg: "./test_tcp_socket 8181")
*     3. Launch another terminal, type the "netstat -a | grep 8181"
* @CreatedTime: 22/5/16
********************************/

void TestForTcpSocket(int argc, char **argv)
{
    TcpSocket test_socket(argc, argv);
    test_socket.CreateSocket();
    // test passed
}

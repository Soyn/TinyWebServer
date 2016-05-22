#ifndef TEST_CASES_HEADER_HPP_INCLUDED
#define TEST_CASES_HEADER_HPP_INCLUDED

/**************************************
* @Author: Soyn
* @Brief: The headrt file for test cases
* @CreaedTime: 18/5/16
***************************************/
#include "../logger.hpp"
#include "../http_server.hpp"
#include "../server_error_handler.hpp"
#include "../tcp_socket.hpp"

void TestForLogger();
void TestForErrorHandler();
void TestForTcpSocket(int argc, char **argv);
void TestForHttpSerever();

#endif // TEST_CASES_HEADER_HPP_INCLUDED

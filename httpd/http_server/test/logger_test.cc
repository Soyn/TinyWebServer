#include "test_cases_header.hpp"

/************************
* @Author: Soyn
* @Brief: Test for logger
* @CreatedTime: 18/5/16
************************/

void TestForLogger()
{
    Logger test_logger;
    int test_socket_file_descriptor;

    /* test the ERROR logging, test case passed
    test_logger.Logging(Logger::ERROR, "test ERROR", "18/5/16",
                        test_socket_file_descriptor);
    */

    /*test the FORBIDDEN logging, test case passed
    test_logger.Logging(Logger::FORBIDDEN, "test FORBBIDDEN", " cheers",
                        test_socket_file_descriptor);
    */


    /* test the LOG logging, test case passed
    test_logger.Logging(Logger::LOG, "fgvgvgy", "sss",
                        test_socket_file_descriptor);
    */

    /* test the NOTFOUND logging, test case passed
    test_logger.Logging(Logger::NOTFOUND, "ffdsf", "hbhbvhj",
                        test_socket_file_descriptor);
    */

    std::cout << "cleaning the log" << std::endl;
    // clean the log file, test passed
    test_logger.CleanLog();
}

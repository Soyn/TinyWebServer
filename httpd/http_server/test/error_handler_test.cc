#include "test_cases_header.hpp"
/*****************************
* @Author: Soyn
* @Brief: Test for error handler
* @CreatedTime: 19/5/16
******************************/
void TestForErrorHandler()
{
    char *chr[] = {"./test", "port", "sbin"};
    ErrorHandler test_error_handler(3,chr);
    test_error_handler.CheckRequestSupportedOrNot();
    test_error_handler.CheckRequestDirectoryValidOrNot();
    test_error_handler.CheckChangeDirectoryValidOrNot();
}

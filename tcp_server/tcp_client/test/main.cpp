/************************************
* @Author: Soyn
* @Brief: Test file for socket client
* @CreatedTime: 26/4/16
*************************************/

#include "../socket_client.h"
#include <iostream>
int main(int argc, char **argv)
{
    Client test_client(argc, argv);
    test_client.Run();
    return 0;
}

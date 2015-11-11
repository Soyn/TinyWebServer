#include <iostream>
#include "HttpServer.h"

using namespace std;

int main(int argc, char **argv)
{
    HttpServer h(argc, argv);
    std :: cout << "I'm happy now!" << std :: endl;
    std :: cout << "Hello world" << std :: endl;
    return 0;
}

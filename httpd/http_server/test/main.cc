#include "../http_server.hpp"

using namespace std;

int main(int argc, char **argv)
{
    HttpServer test1(argc, argv);
    test1.Run();
    return 0;
}

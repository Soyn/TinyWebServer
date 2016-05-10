#include "../socket_server.h"

using namespace std;

int main(int argc, char **argv)
{
    Server test_server(argc, argv);
    test_server.Run();
    return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include "protos/world_ups.pb.h"
#include "Server/BaseServer.hpp"
#include "Utils/utils.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
    try {
        cout << "Starting the server...\n";
        BaseServer server(nullptr, "5555", 10000, 32);
        server.launch();
    } catch (const exception &e) {
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }

    return 0;
}

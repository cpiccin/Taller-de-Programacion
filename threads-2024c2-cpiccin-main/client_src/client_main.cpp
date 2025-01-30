#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "../common_src/socket.h"

#include "client_loop.h"
#include "client_protocol.h"
#include "player.h"


int main(int argc, char* argv[]) {
    if (argc != 3) {
        throw std::runtime_error("Bad program call. Expected: ./client <host> <port>");
    }

    try {
        Client client(argv[1], argv[2]);
        client.run();
        return 0;
    } catch (const std::exception& e) {
        if (std::string(e.what()) == "Exit command received") {
            return 0;
        }
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error" << std::endl;
        return 1;
    }
}

#include "client_loop.h"

Client::Client(const char* direc, const char* port): skt(direc, port) {}

void Client::run() {
    std::cout << INITIAL_MSG;
    std::string name;
    std::getline(std::cin, name);

    Player player(skt, name);
    try {
        while (true) {
            std::string input;
            std::getline(std::cin, input);

            std::vector<std::string> cmd = splitCmd(input, DELIMITER);

            if (cmd[0] == PICKUP_CMD) {
                player.pickup(cmd[1]);
            } else if (cmd[0] == READ_CMD) {
                player.read(cmd[1]);
            } else if (cmd[0] == EXIT_CMD) {
                throw std::runtime_error("Exit command received");
            }
        }
    } catch (const std::runtime_error& e) {
        return;
    }
}

std::vector<std::string> Client::splitCmd(const std::string& s, char delimiter) {
    std::vector<std::string> cmd;
    std::stringstream ss(s);
    std::string item;

    while (std::getline(ss, item, delimiter)) {
        cmd.push_back(item);
    }

    checkValidArgsAmount(cmd);

    return cmd;
}

void Client::checkValidArgsAmount(const std::vector<std::string>& cmd) {
    if (cmd.size() != 2 && cmd[0] != EXIT_CMD) {
        throw std::invalid_argument("Invalid amount of arguments");
    }
}

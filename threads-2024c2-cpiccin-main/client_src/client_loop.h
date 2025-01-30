#ifndef CLIENT_H_
#define CLIENT_H_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../common_src/socket.h"

#include "player.h"

class Client {
private:
    Socket skt;

    std::vector<std::string> splitCmd(const std::string& s, char delimiter);
    void checkValidArgsAmount(const std::vector<std::string>& cmd);

    const std::string INITIAL_MSG = "What is your name?\n";  // cppcheck-suppress unusedStructMember
    const std::string EXIT_CMD = "Exit";                     // cppcheck-suppress unusedStructMember
    const std::string PICKUP_CMD = "Pickup";                 // cppcheck-suppress unusedStructMember
    const std::string READ_CMD = "Read";                     // cppcheck-suppress unusedStructMember
    const char DELIMITER = ' ';                              // cppcheck-suppress unusedStructMember

public:
    Client(const char* direc, const char* port);
    void run();
};

#endif

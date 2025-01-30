#ifndef PLAYER_H_
#define PLAYER_H_
#include <iostream>
#include <memory>  // Include this for std::shared_ptr
#include <sstream>
#include <string>
#include <vector>

#include "../common_src/socket.h"

#include "client_protocol.h"

class Player {
private:
    std::string name;  // cppcheck-suppress unusedStructMember
    ClientProtocol protocol;

    void checkValidBoxId(const int id);

public:
    // cppcheck-suppress constParameter
    Player(Socket& skt, const std::string& name);
    void pickup(const std::string& box_id);
    void read(const std::string& n);
};

#endif  // PLAYER_H_

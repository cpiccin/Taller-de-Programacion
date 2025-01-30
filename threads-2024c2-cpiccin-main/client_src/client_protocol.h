#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <iostream>
#include <memory>  // Include this for std::shared_ptr
#include <stdexcept>
#include <string>

#include "../common_src/protocol.h"
#include "../common_src/socket.h"

#include "parser.h"

class ClientProtocol: public Protocol {
private:
    Parser parser;

    const std::string NEW_BOX_MSG = "A new box has appeared";

public:
    // cppcheck-suppress constParameter
    explicit ClientProtocol(Socket& skt);
    void send(const std::string& player_name, uint8_t box_id);
    std::string receive();
};

#endif  // CLIENT_PROTOCOL_H

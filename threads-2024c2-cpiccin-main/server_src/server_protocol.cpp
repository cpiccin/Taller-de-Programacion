#include "server_protocol.h"

#include <cstring>
#include <iostream>
#include <stdexcept>
// cppcheck-suppress constParameter
ServerProtocol::ServerProtocol(Socket& skt): Protocol(skt) {}

std::pair<std::string, uint8_t> ServerProtocol::receive() {
    bool was_closed = false;
    try {
        uint8_t code = receiveUint8(&was_closed);
        verifyCode(code);
        uint16_t msg_size = receiveUint16(&was_closed);
        std::string msg = receiveString(msg_size, &was_closed);
        uint8_t box_id = receiveUint8(&was_closed);
        return std::make_pair(msg, box_id);
    } catch (const std::exception& e) {
        throw std::runtime_error(e.what());
    }
}


void ServerProtocol::sendNewBoxMsg() {
    sendUint8(SERVER_CODE);
    sendUint8(NEW_BOX_CODE);
}

void ServerProtocol::sendRewardMsg(const std::string& player_name, uint8_t reward_id) {
    sendUint8(SERVER_CODE);
    sendUint8(REWARD_CODE);
    sendUint16(player_name.size());
    sendString(player_name);
    sendUint8(reward_id);
}

void ServerProtocol::verifyCode(uint8_t code) {
    if (code != CLIENT_CODE) {
        throw std::runtime_error("Invalid code");
    }
}

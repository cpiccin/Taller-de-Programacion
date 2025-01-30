#include "client_protocol.h"

#include <cstring>
#include <memory>  // Added this line
#include <string>
#include <vector>

#include <arpa/inet.h>

#include "../common_src/socket.h"
// cppcheck-suppress constParameter
ClientProtocol::ClientProtocol(Socket& skt): Protocol(skt), parser() {}

void ClientProtocol::send(const std::string& player_name, uint8_t box_id) {
    try {
        sendUint8(CLIENT_CODE);
        sendUint16(player_name.size());
        sendString(player_name);
        sendUint8(box_id);
    } catch (const std::exception& e) {
        throw std::runtime_error(e.what());
    }
}

std::string ClientProtocol::receive() {
    // solo se ejecuta receive si es que se hizo un read(n)
    bool was_closed = false;
    try {
        receiveUint8(&was_closed);
        uint8_t code2 = receiveUint8(&was_closed);

        if (code2 == NEW_BOX_CODE) {
            return NEW_BOX_MSG;
        } else if (code2 == REWARD_CODE) {
            uint16_t player_name_len = receiveUint16(&was_closed);
            std::string player_name = receiveString(player_name_len, &was_closed);
            uint8_t box_id = receiveUint8(&was_closed);
            return player_name + " picked up a " + parser.get_box_item(box_id);
        } else {
            throw std::runtime_error("Invalid code");
        }
    } catch (const std::exception& e) {
        if (was_closed) {
            skt.shutdown(2);
            skt.close();
        } else {
            throw std::runtime_error(e.what());
        }
    }
    return "";
}

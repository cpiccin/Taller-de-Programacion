#include "player.h"

#include <iostream>
#include <sstream>
// cppcheck-suppress constParameter
Player::Player(Socket& skt, const std::string& name): name(name), protocol(skt) {}


void Player::pickup(const std::string& box_id) {
    int value = std::stoi(box_id);
    checkValidBoxId(value);

    uint8_t id = static_cast<uint8_t>(value);
    protocol.send(name, id);
}

void Player::read(const std::string& n) {
    int value = std::stoi(n);
    for (int i = 0; i < value; i++) {
        // se bloquea en el receive si es que no hay mensajes para leer
        std::string msg = protocol.receive();
        std::cout << msg << std::endl;
    }
}

void Player::checkValidBoxId(const int id) {
    if (id < 1 || id > 4) {
        std::cerr << "Invalid box id\n";
    }
}

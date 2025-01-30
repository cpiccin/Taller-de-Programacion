#include "client_protocol.h"

#include <cstdint>
#include <cstring>
#include <iostream>
#include <utility>
#include <vector>

#include "../../../../../usr/include/netinet/in.h"

#include "socket.h"
#define GREET_MSG "What arya buying?"

ClientProtocol::ClientProtocol(Socket&& skt): skt(std::move(skt)) {}

int receiveInt();
std::string receiveString();

void ClientProtocol::send(const std::string& msg) {
    bool was_closed = false;
    size_t msg_size = msg.size() + 1;  // +1 para el \0
    skt.sendall(msg.c_str(), msg_size, &was_closed);
}

std::vector<std::string> ClientProtocol::receive() {
    std::string initial_msg = receiveString();
    if (initial_msg == GREET_MSG) {
        std::cout << initial_msg << std::endl;
        return std::vector<std::string>{};
    }
    return receivePlayerInfo(initial_msg);
}

std::vector<std::string> ClientProtocol::receivePlayerInfo(std::string& initial_msg) {
    std::vector<std::string> info;

    info.push_back(initial_msg);

    int primary_ammo = receiveInt();
    info.push_back(std::to_string(primary_ammo));

    std::string secondary_weapon = receiveString();
    info.push_back(secondary_weapon);

    int secondary_ammo = receiveInt();
    info.push_back(std::to_string(secondary_ammo));

    int knife = receiveInt();
    info.push_back(std::to_string(knife));

    return info;
}

std::string ClientProtocol::receiveString() {
    bool was_closed = false;

    char recv_buf[2];
    skt.recvall(recv_buf, sizeof(recv_buf), &was_closed);

    const uint16_t* recuperado_ptr = reinterpret_cast<uint16_t*>(recv_buf);
    uint16_t recuperado = ntohs(*recuperado_ptr);

    std::vector<char> buf_msg(recuperado);
    skt.recvall(buf_msg.data(), recuperado, &was_closed);

    return std::string(buf_msg.data(), buf_msg.size());
}

int ClientProtocol::receiveInt() {
    bool was_closed = false;
    char recv_buf[1];
    skt.recvall(recv_buf, sizeof(recv_buf), &was_closed);

    const uint8_t* recuperado_ptr = reinterpret_cast<uint8_t*>(recv_buf);
    uint8_t recuperado = *recuperado_ptr;
    return static_cast<int>(recuperado);
}

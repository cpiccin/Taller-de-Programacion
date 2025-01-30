#include "server_protocol.h"

#include <cstdint>
#include <cstring>
#include <iostream>
#include <utility>
#include <vector>

#include <arpa/inet.h>

#include "socket.h"
#define GREET_MSG "What arya buying?"


ServerProtocol::ServerProtocol(Socket&& skt): skt(std::move(skt)) {}


void ServerProtocol::sendString(const std::string& msg) {
    bool was_closed = false;

    uint16_t value = msg.length();
    uint16_t hex_value = htons(value);

    char sz_buf[2];
    std::memcpy(sz_buf, &hex_value, 2);
    // envio el tamanio
    skt.sendall(sz_buf, sizeof(sz_buf), &was_closed);
    // envio el mensaje
    skt.sendall(msg.c_str(), msg.length(), &was_closed);
}

void ServerProtocol::sendInt(const std::string& msg) {
    bool was_closed = false;
    int intValue = std::stoi(msg);
    uint8_t uint8Value = static_cast<uint8_t>(intValue);
    char buf[1];
    memcpy(buf, &uint8Value, 1);
    skt.sendall(buf, sizeof(buf), &was_closed);
}

void ServerProtocol::printServerLog(const std::vector<std::string>& log) {
    for (const std::string& elem: log) {
        std::cout << elem << std::endl;
    }
}

void ServerProtocol::send(const std::vector<std::string>& msg) {

    if (msg[0] == GREET_MSG) {
        sendString(msg[0]);
        return;
    }

    sendString(msg[0]);
    sendInt(msg[1]);
    sendString(msg[2]);
    sendInt(msg[3]);
    sendInt(msg[4]);
}

std::string ServerProtocol::receive() {
    bool was_closed = false;
    // porque 512?
    std::vector<char> recv_buf(1);
    std::string result;

    while (true) {
        int received = skt.recvall(recv_buf.data(), recv_buf.size(), &was_closed);
        if (was_closed) {
            return "q";
        }

        result.append(recv_buf.data(), received);

        if (result.find('\0') != std::string::npos) {
            break;
        }
    }

    result.resize(result.find('\0'));
    return result;
}

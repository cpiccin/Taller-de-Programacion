#include "protocol.h"
// cppcheck-suppress constParameter
Protocol::Protocol(Socket& skt): skt(std::move(skt)) {}


uint8_t Protocol::receiveUint8(bool* was_closed) {
    char buf[1];
    skt.recvall(buf, sizeof(buf), was_closed);
    return buf[0];
}

uint16_t Protocol::receiveUint16(bool* was_closed) {
    char buf[2];
    skt.recvall(buf, sizeof(buf), was_closed);
    const uint16_t* num = reinterpret_cast<uint16_t*>(buf);
    return ntohs(*num);
}

std::string Protocol::receiveString(uint16_t str_len, bool* was_closed) {
    std::vector<char> buf(str_len);
    skt.recvall(buf.data(), str_len, was_closed);
    return std::string(buf.data(), buf.size());
}

void Protocol::sendUint8(uint8_t num) {
    bool was_closed = false;
    skt.sendall(reinterpret_cast<char*>(&num), sizeof(num), &was_closed);
}

void Protocol::sendUint16(uint16_t num) {
    // para el largo del mensaje
    bool was_closed = false;
    uint16_t hex_num = htons(num);
    char buf[2];
    std::memcpy(buf, &hex_num, 2);
    skt.sendall(buf, sizeof(buf), &was_closed);
}

void Protocol::sendString(const std::string& str) {
    bool was_closed = false;
    skt.sendall(str.c_str(), str.size(), &was_closed);
}

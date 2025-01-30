#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <cstring>
#include <memory>  // Added this line
#include <string>
#include <utility>
#include <vector>

#include <arpa/inet.h>

#include "socket.h"

class Protocol {
protected:
    Socket skt;

public:
    // cppcheck-suppress constParameter
    explicit Protocol(Socket& skt);

    uint8_t receiveUint8(bool* was_closed);
    uint16_t receiveUint16(bool* was_closed);
    std::string receiveString(uint16_t str_len, bool* was_closed);

    void sendUint8(uint8_t num);
    void sendUint16(uint16_t num);
    void sendString(const std::string& str);

    static const uint8_t CLIENT_CODE = 0x03;   // cppcheck-suppress unusedStructMember
    static const uint8_t SERVER_CODE = 0x06;   // cppcheck-suppress unusedStructMember
    static const uint8_t NEW_BOX_CODE = 0x05;  // cppcheck-suppress unusedStructMember
    static const uint8_t REWARD_CODE = 0x04;   // cppcheck-suppress unusedStructMember
};
#endif  // PROTOCOL_H_

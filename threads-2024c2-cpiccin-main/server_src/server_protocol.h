#ifndef SERVER_PROTOCOL_H_
#define SERVER_PROTOCOL_H_

#include <memory>
#include <string>
#include <utility>

#include "../common_src/protocol.h"

class ServerProtocol: public Protocol {
private:
    void verifyCode(uint8_t code);

public:
    // cppcheck-suppress constParameter
    explicit ServerProtocol(Socket& skt);
    std::pair<std::string, uint8_t> receive();
    void sendNewBoxMsg();
    void sendRewardMsg(const std::string& player_name, uint8_t reward_id);
};

#endif  // SERVER_PROTOCOL_H_

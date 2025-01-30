#include "sender.h"

Sender::Sender(ServerProtocol& protocol, Queue<std::pair<std::string, uint8_t>>& q):
        q(q), protocol(protocol) {}

void Sender::run() {
    while (_keep_running) {
        try {
            std::pair<std::string, uint8_t> msg = q.pop();
            if (msg.second == Protocol::NEW_BOX_CODE) {
                protocol.sendNewBoxMsg();
            } else {
                protocol.sendRewardMsg(msg.first, msg.second);
            }
        } catch (const std::exception& e) {
            _keep_running = false;
        }
    }
}

void Sender::kill() {
    q.close();
    _keep_running = false;
}

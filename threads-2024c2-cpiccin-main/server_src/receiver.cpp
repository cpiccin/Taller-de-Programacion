#include "receiver.h"

Receiver::Receiver(ServerProtocol& protocol, Queue<std::pair<std::string, uint8_t>>& q):
        q(q), protocol(protocol) {}

void Receiver::run() {
    while (_keep_running) {
        try {
            std::pair<std::string, uint8_t> msg = protocol.receive();
            q.push(msg);
        } catch (const std::exception& e) {
            _keep_running = false;
        }
    }
}

void Receiver::kill() { _keep_running = false; }

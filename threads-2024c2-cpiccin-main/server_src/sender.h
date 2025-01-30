#ifndef SENDER_H_
#define SENDER_H_

#include <cstring>
#include <memory>  // Include this for std::shared_ptr
#include <string>
#include <utility>

#include <netinet/in.h>

#include "../common_src/queue.h"
#include "../common_src/socket.h"
#include "../common_src/thread.h"

#include "server_protocol.h"

class Sender: public Thread {
private:
    Queue<std::pair<std::string, uint8_t>>& q;
    ServerProtocol& protocol;

    void run() override;

public:
    Sender(ServerProtocol& protocol, Queue<std::pair<std::string, uint8_t>>& q);

    void kill();
};

#endif  // SENDER_H_

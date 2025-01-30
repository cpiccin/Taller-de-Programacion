#ifndef RECEIVER_H_
#define RECEIVER_H_

#include <iostream>  // Add this for debug prints
#include <memory>    // Include this for std::shared_ptr
#include <string>
#include <utility>

#include <arpa/inet.h>

#include "../common_src/queue.h"
#include "../common_src/socket.h"
#include "../common_src/thread.h"

#include "server_protocol.h"

class Receiver: public Thread {
private:
    Queue<std::pair<std::string, uint8_t>>& q;
    ServerProtocol& protocol;

    void run() override;

public:
    Receiver(ServerProtocol& protocol, Queue<std::pair<std::string, uint8_t>>& q);

    void kill();
};

#endif  // RECEIVER_H_

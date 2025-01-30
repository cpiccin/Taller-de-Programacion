#ifndef CLIENT_H_
#define CLIENT_H_

#include <memory>
#include <string>
#include <utility>

#include "../common_src/queue.h"
#include "../common_src/socket.h"
#include "../common_src/thread.h"

#include "receiver.h"
#include "sender.h"
#include "server_protocol.h"
class Client {
private:
    Socket client;
    Queue<std::pair<std::string, uint8_t>>& recv_q;
    Queue<std::pair<std::string, uint8_t>>& send_q;
    ServerProtocol protocol;
    Receiver receiver_t;
    Sender sender_t;

    void start_run();

public:
    Client(Socket&& client, Queue<std::pair<std::string, uint8_t>>& recv_q,
           Queue<std::pair<std::string, uint8_t>>& send_q);

    void stop();

    void join();

    bool is_alive();
};


#endif  // CLIENT_H_

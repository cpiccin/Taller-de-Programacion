#include <exception>
#include <iostream>  // Add this for debug prints
#include <list>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "../common_src/socket.h"
#include "../common_src/thread.h"

#include "client.h"
#include "receiver.h"
#include "send_queues_monitor.h"
#include "sender.h"
#define MAX_SIZE 100
class Acceptor: public Thread {

private:
    Socket srv;
    std::list<Client*> clients;  // cppcheck-suppress unusedStructMember
    Queue<std::pair<std::string, uint8_t>>& recv_q;
    SendQueuesMonitor& monitor;

    void reap_dead();
    void run() override;

public:
    Acceptor(Socket srv, Queue<std::pair<std::string, uint8_t>>& recv_q,
             SendQueuesMonitor& send_queues_monitor);

    void stop() override;

    void shutdown();
};

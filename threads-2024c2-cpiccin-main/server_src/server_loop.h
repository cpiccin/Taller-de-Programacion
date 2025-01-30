#ifndef SERVER_LOOP_H_
#define SERVER_LOOP_H_

#include <chrono>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <stdio.h>

#include "../common_src/queue.h"
#include "../common_src/socket.h"
#include "../common_src/thread.h"

#include "acceptor.h"
#include "mistery_boxes.h"
#include "read_input.h"
#include "send_queues_monitor.h"
#define MAX_SIZE 100
#define SLEEP 200
#define NEW_BOX_MSG "A new box has appeared"


class Server {
private:
    Socket srv;
    MisteryBoxes mistery_boxes;
    Queue<std::pair<std::string, uint8_t>> recv_queue;
    SendQueuesMonitor monitor;


    std::vector<std::pair<std::string, uint8_t>> recvCmds();
    void processRecvCmds(const std::vector<std::pair<std::string, uint8_t>>& recv_cmds,
                         std::vector<std::string>& server_msgs,
                         std::vector<std::pair<std::string, uint8_t>>& msgs_to_broadcast);
    void addNewBoxesMsgs(std::vector<std::string>& server_msgs,
                         std::vector<std::pair<std::string, uint8_t>>& msgs_to_broadcast);
    void broadcastMsgs(const std::vector<std::pair<std::string, uint8_t>>& msgs_to_broadcast);
    void printServerMsgs(const std::vector<std::string>& server_msgs);

public:
    explicit Server(const char* port);
    void run();
};


#endif

#ifndef SEND_QUEUES_MONITOR_H
#define SEND_QUEUES_MONITOR_H

#include <mutex>
#include <string>
#include <utility>
#include <vector>

#include "../common_src/queue.h"

class SendQueuesMonitor {
private:
    std::mutex m;
    std::vector<Queue<std::pair<std::string, uint8_t>>*>
            send_queues;  // cppcheck-suppress unusedStructMember

public:
    SendQueuesMonitor();

    SendQueuesMonitor(const SendQueuesMonitor&) = delete;
    SendQueuesMonitor& operator=(const SendQueuesMonitor&) = delete;

    void broadcast(const std::vector<std::pair<std::string, uint8_t>>& msgs_to_broadcast);
    void addQueue(Queue<std::pair<std::string, uint8_t>>* queue);
    void removeAllQueues();
};

#endif  // SEND_QUEUES_MONITOR_H

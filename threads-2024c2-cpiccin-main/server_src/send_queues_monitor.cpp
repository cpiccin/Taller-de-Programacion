#include "send_queues_monitor.h"

SendQueuesMonitor::SendQueuesMonitor(): m(), send_queues() {}


void SendQueuesMonitor::broadcast(
        const std::vector<std::pair<std::string, uint8_t>>& msgs_to_broadcast) {
    std::lock_guard<std::mutex> lock(m);
    for (const auto& msg: msgs_to_broadcast) {
        for (auto& q: send_queues) {
            q->push(msg);
        }
    }
}

void SendQueuesMonitor::addQueue(Queue<std::pair<std::string, uint8_t>>* queue) {
    std::lock_guard<std::mutex> lock(m);
    send_queues.push_back(queue);
}

void SendQueuesMonitor::removeAllQueues() {
    std::lock_guard<std::mutex> lock(m);
    for (auto& q: send_queues) {
        delete q;
    }
    send_queues.clear();
}

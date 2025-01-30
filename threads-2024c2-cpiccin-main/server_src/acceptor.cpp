#include "acceptor.h"

Acceptor::Acceptor(Socket srv, Queue<std::pair<std::string, uint8_t>>& recv_q,
                   SendQueuesMonitor& send_queues):
        srv(std::move(srv)), recv_q(recv_q), monitor(send_queues) {}


void Acceptor::run() {
    try {
        while (_keep_running) {
            // shared_ptr es thread-safe !!!!
            Socket new_client_skt = srv.accept();

            Queue<std::pair<std::string, uint8_t>>* new_q =
                    new Queue<std::pair<std::string, uint8_t>>(MAX_SIZE);
            monitor.addQueue(new_q);

            Client* new_client = new Client(std::move(new_client_skt), recv_q, *new_q);
            clients.push_back(new_client);

            reap_dead();
        }
    } catch (const std::exception& e) {
        _keep_running = false;
    }
}

void Acceptor::reap_dead() {
    clients.remove_if([](Client* c) {
        if (!c->is_alive()) {
            c->stop();
            c->join();
            delete c;
            return true;
        }
        return false;
    });
}

void Acceptor::stop() {
    srv.shutdown(2);
    _keep_running = false;
    recv_q.close();
}

void Acceptor::shutdown() {
    for (auto& client: clients) {
        client->stop();
        client->join();
        delete client;
    }
    clients.clear();
    monitor.removeAllQueues();
}

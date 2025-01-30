#include "client.h"

Client::Client(Socket&& client, Queue<std::pair<std::string, uint8_t>>& recv_q,
               Queue<std::pair<std::string, uint8_t>>& send_q):
        client(std::move(client)),
        recv_q(recv_q),
        send_q(send_q),
        protocol(this->client),
        receiver_t(protocol, recv_q),
        sender_t(protocol, send_q) 
{
    start_run();
}

void Client::start_run() {
    try {
        receiver_t.start();
        sender_t.start();
    } catch (std::exception& e) {
        std::cout << "Error en client:" << e.what() << std::endl;
    }
}

void Client::stop() {
    receiver_t.kill();
    sender_t.kill();
}

void Client::join() {
    receiver_t.join();
    sender_t.join();
}


bool Client::is_alive() {
    return receiver_t.is_alive() && sender_t.is_alive();
}

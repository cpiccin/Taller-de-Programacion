#include "server_loop.h"

Server::Server(const char* port): srv(port), mistery_boxes(), recv_queue(MAX_SIZE), monitor() {}

void Server::run() {
    Acceptor acceptor(std::move(srv), recv_queue, monitor);
    acceptor.start();

    // thread lector de input
    ReadInput read_input_t;
    read_input_t.start();

    while (read_input_t.is_alive()) {
        try {
            mistery_boxes.updateTimers();

            std::vector<std::string> server_msgs;
            std::vector<std::pair<std::string, uint8_t>> msgs_to_broadcast;

            std::vector<std::pair<std::string, uint8_t>> recv_cmds = recvCmds();
            processRecvCmds(recv_cmds, server_msgs, msgs_to_broadcast);
            addNewBoxesMsgs(server_msgs, msgs_to_broadcast);
            printServerMsgs(server_msgs);
            broadcastMsgs(msgs_to_broadcast);

            std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP));
        } catch (const std::exception& e) {
            if (std::string(e.what()) == "Connection closed") {
                // ignoro porque por ahora no me importa que se desconecto alguien
                continue;
            }
            throw;
        }
    }
    acceptor.stop();
    acceptor.shutdown();
    acceptor.join();

    read_input_t.join();
}

std::vector<std::pair<std::string, uint8_t>> Server::recvCmds() {
    std::pair<std::string, uint8_t> msg;
    std::vector<std::pair<std::string, uint8_t>> recv_msgs;
    while (recv_queue.try_pop(msg)) {
        recv_msgs.push_back(msg);
    }
    return recv_msgs;
}

void Server::processRecvCmds(const std::vector<std::pair<std::string, uint8_t>>& recv_cmds,
                             std::vector<std::string>& server_msgs,
                             std::vector<std::pair<std::string, uint8_t>>& msgs_to_broadcast) {
    for (const auto& cmd: recv_cmds) {
        std::string player_name = cmd.first;
        uint8_t box_id = cmd.second;
        if (mistery_boxes.is_available(box_id)) {
            std::string msg = player_name + " picked up a " + mistery_boxes.get_box_item(box_id);
            server_msgs.push_back(msg);
            msgs_to_broadcast.push_back(
                    std::make_pair(player_name, mistery_boxes.get_reward_id(box_id)));
        }
    }
}

void Server::addNewBoxesMsgs(std::vector<std::string>& server_msgs,
                             std::vector<std::pair<std::string, uint8_t>>& msgs_to_broadcast) {
    int n = mistery_boxes.newBoxesAmount();
    for (int i = 0; i < n; i++) {
        server_msgs.push_back(NEW_BOX_MSG);
        msgs_to_broadcast.push_back(std::make_pair("", 0x05));
    }
}

void Server::printServerMsgs(const std::vector<std::string>& server_msgs) {
    for (const auto& server_msg: server_msgs) {
        std::cout << server_msg << std::endl;
    }
}

void Server::broadcastMsgs(const std::vector<std::pair<std::string, uint8_t>>& msgs_to_broadcast) {
    monitor.broadcast(msgs_to_broadcast);
}

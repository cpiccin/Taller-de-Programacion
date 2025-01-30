#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <cstdint>
#include <string>
#include <vector>

#include "player_client.h"
#include "socket.h"

class ClientProtocol {
private:
    Socket skt;

    /*
        Recibe un string del socket y lo devuelve.
    */
    std::string receiveString();
    /*
        Recibe un uint8_t del socket y lo devuelve como int.
    */
    int receiveInt();
    /*
        Recibe la informacion del jugador enviada desde el servidor y la devuelve en un vector de
       strings.
    */
    std::vector<std::string> receivePlayerInfo(std::string& initial_msg);

public:
    explicit ClientProtocol(Socket&& skt);
    /*
        Envia un mensaje (string) al servidor.
    */
    void send(const std::string& msg);
    /*
        Recibe un mensaje del servidor y lo devuelve en un vector de strings.
    */
    std::vector<std::string> receive();
};

#endif  // CLIENT_PROTOCOL_H

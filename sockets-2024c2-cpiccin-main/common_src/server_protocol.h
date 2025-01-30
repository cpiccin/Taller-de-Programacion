#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <string>
#include <vector>

#include "player_server.h"  // Asegúrate de incluir la definición de Player
#include "socket.h"

class ServerProtocol {
private:
    Socket skt;

    /*
        Envia strings respetando el protocolo: <payload length><payload>
        - El payload length es un entero de 16 bits sin signo (uint16_t)
        - El payload es el mensaje a enviar (tira de bytes)
    */
    void sendString(const std::string& msg);
    /*
        Envia enteros respetando el protocolo. Los recibe como strings,
        y los envia como un entero de 8 bits sin signo (uint8_t)
    */
    void sendInt(const std::string& msg);

public:
    explicit ServerProtocol(Socket&& skt);
    /*
        Envia informacion contenida en un vector.
    */
    void send(const std::vector<std::string>& msg);
    /*
        Recibe un mensaje (string) enviado por el cliente y lo devuelve
    */
    std::string receive();
    /*
        Imprime la secuencia de transacciones entre el cliente y el servidor
    */
    void printServerLog(const std::vector<std::string>& log);
};

#endif  // SERVER_PROTOCOL_H

#include <cstdint>
#include <exception>
#include <iomanip>
#include <iostream>

#include "../common_src/player_server.h"
#include "../common_src/server_protocol.h"
#include "../common_src/socket.h"

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "Bad program call. Expected " << argv[0] << " <port>\n";
        return 1;
    }

    Socket srv(argv[1]);

    Socket peer = srv.accept();

    PlayerServer player;

    ServerProtocol protocol(std::move(peer));

    protocol.send(std::vector<std::string>{"What arya buying?"});

    while (true) {
        // se reciben indicaciones del cliente
        std::string client_input = protocol.receive();

        if (client_input == "q") {
            // en receive() se devolvio "q" porque se detecto que was_closed==true
            break;
        }

        // se actualiza dadas esas indicaciones
        std::vector<std::string> secuencia_de_transacciones =
                player.updateDadoMsgNuevo(client_input);
        // se imprime la secuencia de transacciones
        protocol.printServerLog(secuencia_de_transacciones);
        // se envia la informacion actualizada del player
        protocol.send(player.getPlayerInfo());
    }
    return 0;
}

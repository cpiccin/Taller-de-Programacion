#include <cstdint>
#include <cstring>
#include <exception>
#include <iostream>

#include "../common_src/client_protocol.h"
#include "../common_src/player_client.h"
#include "../common_src/socket.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Bad program call. Expected " << argv[0] << " <hostname> <port>\n";
        return 1;
    }

    Socket client(argv[1], argv[2]);

    PlayerClient player;

    ClientProtocol protocol(std::move(client));

    protocol.receive();

    while (true) {

        std::string input;
        std::getline(std::cin, input);

        if (input == "q") {
            break;
        }
        // se envia un mensaje
        protocol.send(input);
        // se obtiene la respuesta
        std::vector<std::string> updated_player_info = protocol.receive();
        // se actualiza el jugador
        player.updateInventario(updated_player_info);
        // se imprime el inventario
        player.printInventario();
    }
    return 0;
}

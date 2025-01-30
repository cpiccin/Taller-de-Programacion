#ifndef PLAYER_SERVER_H
#define PLAYER_SERVER_H

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class PlayerServer {
private:
    std::unordered_map<std::string, std::pair<std::string, int>>
            inventario;  // cppcheck-suppress unusedStructMember
    /* Actualiza el arma principal y la devuelve */
    std::string updatePrimaryWeapon(std::string weapon);
    /* Actualiza el arma secundaria y la devuelve */
    std::string updateSecondaryWeapon(std::string weapon);
    /* Actualiza el estado del cuchillo y la devuelve */
    std::string updateKnife();
    /* Devuelve el arma equipada */
    std::string getEquipado(const std::string& key);
    /* Devuelve la cantidad de municiones */
    int getAmmo(const std::string& key);
    /* Actualiza la cantidad de municiones y la devuelve */
    int updateAmmo(const std::string& key, int ammo);

public:
    /* Constructor */
    PlayerServer();
    /*
        Devuelve en un vector la informacion del jugador:
        [string Primary Weapon, int Primary Ammo, string Seconday Weapon, int Secondary Ammo, int
       Knife Equipped]
    */
    std::vector<std::string> getPlayerInfo();
    /*
        Dado un mensaje recibido, decodifica el mensaje, actualiza la info del jugador
        y devuelve un vector con la secuencia de actualizaciones.
    */
    std::vector<std::string> updateDadoMsgNuevo(const std::string& msg);
};

#endif

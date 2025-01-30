#ifndef PLAYER_CLIENT_H
#define PLAYER_CLIENT_H

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class PlayerClient {
private:
    std::unordered_map<std::string, std::pair<std::string, int>>
            inventario;  // cppcheck-suppress unusedStructMember
    /* Cambia el arma primaria por la que se recibe por parametro, seteando la municion segun el
     * valor de ammo */
    void updatePrimaryWeapon(std::string weapon, int ammo);
    /* Cambia el arma secundaria por la que se recibe por parametro, seteando la municion segun el
     * valor de ammo */
    void updateSecondaryWeapon(std::string weapon, int ammo);
    /* Cambia el estado equipado o desequipado del cuchillo segun lo que se reciba por parametro */
    void updateKnife(int equip);
    /* Devuelve el arma equipada o el estado del cuchillo:
     * Puede recibir "Primary Weapon", "Secondary Weapon" o "Knife Equipped" */
    std::string getEquipado(const std::string& key);
    /* Devuelve la municion del arma recibida por parametro */
    int getAmmo(const std::string& key);

public:
    /* Constructor
     * Representa una instancia de jugador con un inventario inicial vacio
     */
    PlayerClient();
    /* Actualiza el inventario con la informacion recibida en un vector con el formato:
     *  [string Primary Weapon, int Primary Ammo, string Seconday Weapon, int Secondary Ammo, int
     * Knife Equipped]
     */
    void updateInventario(const std::vector<std::string>& info);
    /* Imprime el inventario del jugador */
    void printInventario();
};

#endif  // PLAYER_CLIENT_H

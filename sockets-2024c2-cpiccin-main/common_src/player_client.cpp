#include "player_client.h"

#include <iostream>
#include <utility>

PlayerClient::PlayerClient() {
    // estado inicial del diccionario
    inventario["Primary Weapon"] = {"Not Equipped", 0};
    inventario["Secondary Weapon"] = {"Not Equipped", 0};
    inventario["Knife Equipped"] = {"No", 0};
}

void PlayerClient::updatePrimaryWeapon(std::string weapon, int ammo) {
    inventario["Primary Weapon"] = {weapon, ammo};
}

void PlayerClient::updateSecondaryWeapon(std::string weapon, int ammo) {
    inventario["Secondary Weapon"] = {weapon, ammo};
}

void PlayerClient::updateKnife(int equip) {
    // si el cuchillo esta equipado, se desequipa, si no esta equipado, se equipa
    inventario["Knife Equipped"] = {(equip == 1) ? "Yes" : "No", equip};
}

void PlayerClient::updateInventario(const std::vector<std::string>& info) {
    updatePrimaryWeapon(info[0], std::stoi(info[1]));
    updateSecondaryWeapon(info[2], std::stoi(info[3]));
    updateKnife(std::stoi(info[4]));
}

std::string PlayerClient::getEquipado(const std::string& key) { return inventario[key].first; }

int PlayerClient::getAmmo(const std::string& key) { return inventario[key].second; }

void PlayerClient::printInventario() {
    std::cout << "Primary Weapon: " << getEquipado("Primary Weapon")
              << " | Ammo: " << getAmmo("Primary Weapon") << std::endl;
    std::cout << "Secondary Weapon: " << getEquipado("Secondary Weapon")
              << " | Ammo: " << getAmmo("Secondary Weapon") << std::endl;
    std::cout << "Knife Equipped: " << getEquipado("Knife Equipped") << "\n" << std::endl;
}

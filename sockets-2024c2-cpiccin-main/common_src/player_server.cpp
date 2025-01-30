#include "player_server.h"

#include <iostream>
#include <string>
#include <vector>

PlayerServer::PlayerServer() {
    inventario["Primary Weapon"] = {"Not Equipped", 0};
    inventario["Secondary Weapon"] = {"Not Equipped", 0};
    inventario["Knife Equipped"] = {"No", 0};
}

std::string PlayerServer::updatePrimaryWeapon(std::string weapon) {
    inventario["Primary Weapon"] = {weapon, 0};
    return weapon;
}

std::string PlayerServer::updateSecondaryWeapon(std::string weapon) {
    inventario["Secondary Weapon"] = {weapon, 0};
    return weapon;
}

std::string PlayerServer::updateKnife() {
    if (getEquipado("Knife Equipped") == "Yes") {
        inventario["Knife Equipped"] = {"No", 0};
        return "Knife not equipped";
    } else {
        inventario["Knife Equipped"] = {"Yes", 1};
        return "Equipped knife";
    }
}

std::string PlayerServer::getEquipado(const std::string& key) { return inventario[key].first; }

int PlayerServer::getAmmo(const std::string& key) { return inventario[key].second; }

int PlayerServer::updateAmmo(const std::string& key, int ammo) {
    if (getEquipado(key) == "Not Equipped")
        return 0;
    inventario[key].second += ammo;
    return inventario[key].second;
}

std::vector<std::string> PlayerServer::getPlayerInfo() {
    std::vector<std::string> info;
    info.push_back(getEquipado("Primary Weapon"));
    info.push_back(std::to_string(getAmmo("Primary Weapon")));
    info.push_back(getEquipado("Secondary Weapon"));
    info.push_back(std::to_string(getAmmo("Secondary Weapon")));
    info.push_back((getEquipado("Knife Equipped") == "Yes") ? std::to_string(1) :
                                                              std::to_string(0));
    return info;
}

std::vector<std::string> PlayerServer::updateDadoMsgNuevo(const std::string& msg) {
    std::vector<std::string> info;
    for (char c: msg.substr(1)) {
        switch (c) {
            case '1':
                info.push_back(updateSecondaryWeapon("Banana"));
                break;
            case '2':
                info.push_back(updateSecondaryWeapon("Magnum"));
                break;
            case '3':
                info.push_back(updateSecondaryWeapon("Old Pistol"));
                break;
            case '4':
                info.push_back(updatePrimaryWeapon("Pew Pew Laser"));
                break;
            case '5':
                info.push_back(updatePrimaryWeapon("Phaser"));
                break;
            case '6':
                info.push_back(updatePrimaryWeapon("Chaindart"));
                break;
            case '7':
                info.push_back("Secondary Ammo: " +
                               std::to_string(updateAmmo("Secondary Weapon", 7)));
                break;
            case '8':
                info.push_back("Primary Ammo: " + std::to_string(updateAmmo("Primary Weapon", 10)));
                break;
            case '9':
                info.push_back(updateKnife());
                break;
            default:
                break;
        }
    }
    return info;
}

#ifndef MISTERY_BOXES_H
#define MISTERY_BOXES_H
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>

class MisteryBoxes {
private:
    std::unordered_map<std::string, int> boxes;  // cppcheck-suppress unusedStructMember
    bool checkTimer(const std::string& box_name, const int time);

public:
    MisteryBoxes();
    /* Se suma 1 al timer de cada caja con cada iteracion que pasa */
    void updateTimers();
    bool is_available(uint8_t box_id);
    std::string get_box_item(uint8_t box_id);
    int newBoxesAmount();
    uint8_t get_reward_id(uint8_t box_id);
    const int BAZOOKA_TIME = 15;    // cppcheck-suppress unusedStructMember
    const int CHAINSAW_TIME = 5;    // cppcheck-suppress unusedStructMember
    const int DEATH_RAY_TIME = 20;  // cppcheck-suppress unusedStructMember
    const int SHOTGUN_TIME = 10;    // cppcheck-suppress unusedStructMember
};

#endif

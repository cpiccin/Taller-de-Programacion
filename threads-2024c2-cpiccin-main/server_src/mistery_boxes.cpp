#include "mistery_boxes.h"


MisteryBoxes::MisteryBoxes() {
    boxes = {
            {"Bazooka", BAZOOKA_TIME + 1},
            {"Chainsaw", CHAINSAW_TIME + 1},
            {"Death ray", DEATH_RAY_TIME + 1},
            {"Shotgun", SHOTGUN_TIME + 1},
    };
}
void MisteryBoxes::updateTimers() {
    for (auto& box: boxes) {
        box.second++;
    }
}

bool MisteryBoxes::is_available(uint8_t box_id) {
    switch (box_id) {
        case 0x01:
            return checkTimer("Bazooka", BAZOOKA_TIME);
        case 0x02:
            return checkTimer("Chainsaw", CHAINSAW_TIME);
        case 0x03:
            return checkTimer("Death ray", DEATH_RAY_TIME);
        case 0x04:
            return checkTimer("Shotgun", SHOTGUN_TIME);
        default:
            return false;
    }
}

bool MisteryBoxes::checkTimer(const std::string& box_name, const int time) {
    if (boxes[box_name] < time) {
        return false;
    } else {
        boxes[box_name] = 0;
        return true;
    }
}

int MisteryBoxes::newBoxesAmount() {
    int new_boxes = 0;
    if (boxes["Bazooka"] == BAZOOKA_TIME) {
        new_boxes++;
    }
    if (boxes["Chainsaw"] == CHAINSAW_TIME) {
        new_boxes++;
    }
    if (boxes["Death ray"] == DEATH_RAY_TIME) {
        new_boxes++;
    }
    if (boxes["Shotgun"] == SHOTGUN_TIME) {
        new_boxes++;
    }
    return new_boxes;
}

uint8_t MisteryBoxes::get_reward_id(uint8_t box_id) {
    switch (box_id) {
        case 0x01:
            return 0x10;
        case 0x02:
            return 0x11;
        case 0x03:
            return 0x12;
        case 0x04:
            return 0x13;
        default:
            return 0x00;
    }
}

std::string MisteryBoxes::get_box_item(uint8_t box_id) {
    std::string item;
    switch (box_id) {
        case 0x01:
            item = "Bazooka";
            break;
        case 0x02:
            item = "Chainsaw";
            break;
        case 0x03:
            item = "Death ray";
            break;
        case 0x04:
            item = "Shotgun";
            break;
        default:
            break;
    }
    return item;
}

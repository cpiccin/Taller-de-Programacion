#include "parser.h"

Parser::Parser() {}

std::string Parser::get_box_item(uint8_t box_id) {
    switch (box_id) {
        case BAZOOKA_CODE:
            return BAZOOKA_ITEM;
        case CHAINSAW_CODE:
            return CHAINSAW_ITEM;
        case DEATH_RAY_CODE:
            return DEATH_RAY_ITEM;
        case SHOTGUN_CODE:
            return SHOTGUN_ITEM;
        default:
            return "";
    }
}

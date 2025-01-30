#ifndef PARSER_H_
#define PARSER_H_

#include <cstdint>
#include <string>

class Parser {
private:
    static constexpr const char* BAZOOKA_ITEM = "Bazooka";  // cppcheck-suppress unusedStructMember
    // cppcheck-suppress unusedStructMember
    static constexpr const char* CHAINSAW_ITEM = "Chainsaw";
    // cppcheck-suppress unusedStructMember
    static constexpr const char* DEATH_RAY_ITEM = "Death ray";
    static constexpr const char* SHOTGUN_ITEM = "Shotgun";  // cppcheck-suppress unusedStructMember

    static constexpr uint8_t BAZOOKA_CODE = 0x10;    // cppcheck-suppress unusedStructMember
    static constexpr uint8_t CHAINSAW_CODE = 0x11;   // cppcheck-suppress unusedStructMember
    static constexpr uint8_t DEATH_RAY_CODE = 0x12;  // cppcheck-suppress unusedStructMember
    static constexpr uint8_t SHOTGUN_CODE = 0x13;    // cppcheck-suppress unusedStructMember

public:
    Parser();
    std::string get_box_item(uint8_t box_id);
};

#endif

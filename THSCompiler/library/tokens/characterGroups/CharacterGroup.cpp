#pragma once

#include <vector>
#include <string>

class CharacterGroup {
public:
    CharacterGroup();
    CharacterGroup(std::vector<std::string> characters);
    CharacterGroup(std::vector<CharacterGroup> characterGroups);
    CharacterGroup(std::vector<std::string> characters, std::vector<CharacterGroup> characterGroups);
    ~CharacterGroup();

    bool Contains(std::string character);

    static CharacterGroup Empty() {
        return CharacterGroup();
    }
    
    std::vector<std::string> characters;
};

CharacterGroup::CharacterGroup() {
    characters = std::vector<std::string>();
}

CharacterGroup::CharacterGroup(std::vector<std::string> characters) {
    this->characters = characters;
}

CharacterGroup::CharacterGroup(std::vector<CharacterGroup> characterGroups) {
    for (CharacterGroup group : characterGroups) {
        for (std::string character : group.characters) {
            this->characters.push_back(character);
        }
    }
}

CharacterGroup::CharacterGroup(std::vector<std::string> characters, std::vector<CharacterGroup> characterGroups) {
    this->characters = characters;

    for (CharacterGroup group : characterGroups) {
        for (std::string character : group.characters) {
            this->characters.push_back(character);
        }
    }
}

CharacterGroup::~CharacterGroup() {
}

bool CharacterGroup::Contains(std::string character) {
    for (std::string c : characters) {
        if (c == character) {
            return true;
        }
    }

    return false;
}
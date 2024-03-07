#pragma once

#include <vector>
#include <string>

class CharacterGroup {
public:
    CharacterGroup(std::vector<std::string> characters);
    CharacterGroup(std::vector<CharacterGroup> characterGroups);
    ~CharacterGroup();

    bool Contains(std::string character);

private:
    std::vector<std::string> characters;
};

CharacterGroup::CharacterGroup(std::vector<std::string> characters) {
    this->characters = characters;
}

CharacterGroup::CharacterGroup(std::vector<CharacterGroup> characterGroups) {
    for (CharacterGroup group : characterGroups) {
        for (std::string character : group.characters) {
            characters.push_back(character);
        }
    }
}

CharacterGroup::~CharacterGroup() {
    characters.clear();
}

bool CharacterGroup::Contains(std::string character) {
    for (std::string c : characters) {
        if (c == character) {
            return true;
        }
    }

    return false;
}
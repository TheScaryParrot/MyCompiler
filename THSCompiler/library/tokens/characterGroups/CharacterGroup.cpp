#pragma once

#include <vector>
#include <string>

class CharacterGroup {
public:
    CharacterGroup(std::vector<std::string>* characters = nullptr, std::vector<CharacterGroup>* characterGroups = nullptr);
    ~CharacterGroup();

    bool Contains(std::string character);

private:
    std::vector<std::string> characters;
};

CharacterGroup::CharacterGroup(std::vector<std::string>* characters, std::vector<CharacterGroup>* characterGroups) {
    if (characters == nullptr) {
        this->characters = std::vector<std::string>();
    }
    else
    {
        this->characters = *characters;
    }
    
    if (characterGroups == nullptr) {
        return;
    }

    for (CharacterGroup group : *characterGroups) {
        for (std::string character : group.characters) {
            this->characters.push_back(character);
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
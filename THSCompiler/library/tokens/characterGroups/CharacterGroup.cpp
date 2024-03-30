#pragma once

#include <vector>
#include <string>

class CharacterGroup {
public:
    CharacterGroup();
    CharacterGroup(std::vector<std::string> strings);
    CharacterGroup(std::vector<CharacterGroup> characterGroups);
    CharacterGroup(std::vector<std::string> strings, std::vector<CharacterGroup> characterGroups);
    ~CharacterGroup();

    bool Contains(std::string character);

    static CharacterGroup Empty() {
        return CharacterGroup();
    }

private:
    std::vector<std::string> strings;
};

CharacterGroup::CharacterGroup() {
    strings = std::vector<std::string>();
}

CharacterGroup::CharacterGroup(std::vector<std::string> strings) {
    this->strings = strings;
}

CharacterGroup::CharacterGroup(std::vector<CharacterGroup> characterGroups) {
    for (CharacterGroup group : characterGroups) {
        for (std::string character : group.strings) {
            this->strings.push_back(character);
        }
    }
}

CharacterGroup::CharacterGroup(std::vector<std::string> strings, std::vector<CharacterGroup> characterGroups) {
    this->strings = strings;

    for (CharacterGroup group : characterGroups) {
        for (std::string character : group.strings) {
            this->strings.push_back(character);
        }
    }
}

CharacterGroup::~CharacterGroup() {
}

bool CharacterGroup::Contains(std::string otherString) {
    for (std::string containedString : strings) {
        if (containedString == otherString) {
            return true;
        }
    }

    return false;
}
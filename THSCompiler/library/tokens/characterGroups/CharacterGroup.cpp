#pragma once

#include "TwoChar.cpp"

#include <vector>
class CharacterGroup {
public:
    CharacterGroup();
    CharacterGroup(std::vector<TwoChar> twoChars);
    CharacterGroup(std::vector<CharacterGroup> characterGroups);
    CharacterGroup(std::vector<TwoChar> twoChars, std::vector<CharacterGroup> characterGroups);
    ~CharacterGroup();

    /// @brief Returns how many characters match the given characterGroup. First not 0 is returned.
    /// @return 0 = no match, 1 = first character matches, 2 = both characters match
    unsigned int Match(char first, char second);

    static CharacterGroup Empty() {
        return CharacterGroup();
    }

private:
    std::vector<TwoChar> twoChars;
};

CharacterGroup::CharacterGroup() {
    twoChars = std::vector<TwoChar>();
}

CharacterGroup::CharacterGroup(std::vector<TwoChar> twoChars) {
    this->twoChars = twoChars;
}

CharacterGroup::CharacterGroup(std::vector<CharacterGroup> characterGroups) {
    for (CharacterGroup group : characterGroups) {
        for (TwoChar twoChar : group.twoChars) {
            this->twoChars.push_back(twoChar);
        }
    }
}

CharacterGroup::CharacterGroup(std::vector<TwoChar> twoChars, std::vector<CharacterGroup> characterGroups) {
    this->twoChars = twoChars;

    for (CharacterGroup group : characterGroups) {
        for (TwoChar twoChar : group.twoChars) {
            this->twoChars.push_back(twoChar);
        }
    }
}

CharacterGroup::~CharacterGroup() {
}

unsigned int CharacterGroup::Match(char first, char second)
{
    unsigned int match = 0;

    for (TwoChar twoChar : twoChars) {
        match = twoChar.Match(first, second);

        if (match > 0) return match;
    }

    return 0;
}
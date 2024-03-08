#pragma once

#include <vector>
#include <string>

#include "CharacterGroup.cpp"

static class CharacterGroups {
public:
    CharacterGroup WHITESPACES = CharacterGroup(std::vector<std::string>{" ", "\n", "\t", "\r"});
    CharacterGroup STATEMENT_END = CharacterGroup(std::vector<std::string>{";"});
    CharacterGroup LOWER_ALPHABET = CharacterGroup(std::vector<std::string>{"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"});
    CharacterGroup UPPER_ALPHABET = CharacterGroup(std::vector<std::string>{"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"});
    CharacterGroup ALPHABET = CharacterGroup(std::vector<CharacterGroup>{LOWER_ALPHABET, UPPER_ALPHABET});
    CharacterGroup NUMBERS = CharacterGroup(std::vector<std::string>{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"});
    CharacterGroup ALPHANUMERIC = CharacterGroup(std::vector<CharacterGroup>{ALPHABET, NUMBERS});
    CharacterGroup BODY_OPEN = CharacterGroup(std::vector<std::string>{"{"});
    CharacterGroup BODY_CLOSE = CharacterGroup(std::vector<std::string>{"}"});
    CharacterGroup PARENTHESIS_OPEN = CharacterGroup(std::vector<std::string>{"("});
    CharacterGroup PARENTHESIS_CLOSE = CharacterGroup(std::vector<std::string>{")"});

}CharacterGroups;
#pragma once

#include <vector>
#include <string>

#include "CharacterGroup.cpp"

static class CharacterGroups {
public:
    CharacterGroups();
    ~CharacterGroups();

    CharacterGroup WHITESPACES = CharacterGroup(std::vector<std::string>{" ", "\n", "\t", "\r"});
    CharacterGroup STATEMENT_END = CharacterGroup(std::vector<std::string>{";"});

    CharacterGroup LOWER_ALPHABET = CharacterGroup(std::vector<std::string>{"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"});
    CharacterGroup UPPER_ALPHABET = CharacterGroup(std::vector<std::string>{"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"});
    CharacterGroup ALPHABET = CharacterGroup(std::vector<std::string>(), std::vector<CharacterGroup>{LOWER_ALPHABET, UPPER_ALPHABET});
    CharacterGroup NUMBERS = CharacterGroup(std::vector<std::string>{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"});
    CharacterGroup ALPHANUMERIC = CharacterGroup(std::vector<CharacterGroup>{ALPHABET, NUMBERS});

    CharacterGroup IDENTIFIER_START_CHAR = CharacterGroup(std::vector<std::string>{"_"}, std::vector<CharacterGroup>{ALPHABET});
    CharacterGroup IDENTIFIER_CHAR = CharacterGroup(std::vector<std::string>{"_"}, std::vector<CharacterGroup>{ALPHABET, NUMBERS});

    CharacterGroup BODY_OPEN = CharacterGroup(std::vector<std::string>{"{"});
    CharacterGroup BODY_CLOSE = CharacterGroup(std::vector<std::string>{"}"});
    CharacterGroup PARENTHESIS_OPEN = CharacterGroup(std::vector<std::string>{"("});
    CharacterGroup PARENTHESIS_CLOSE = CharacterGroup(std::vector<std::string>{")"});
    CharacterGroup SEPERATOR = CharacterGroup(std::vector<std::string>{","});

    CharacterGroup EQUAL_OPERATOR = CharacterGroup(std::vector<std::string>{"=="});
    CharacterGroup NOT_EQUAL_OPERATOR = CharacterGroup(std::vector<std::string>{"!="});
    CharacterGroup GREATER_THAN_OPERATOR = CharacterGroup(std::vector<std::string>{">"});
    CharacterGroup LESS_THAN_OPERATOR = CharacterGroup(std::vector<std::string>{"<"});
    CharacterGroup GREATER_THAN_OR_EQUAL_OPERATOR = CharacterGroup(std::vector<std::string>{">="});
    CharacterGroup LESS_THAN_OR_EQUAL_OPERATOR = CharacterGroup(std::vector<std::string>{"<="});

    CharacterGroup ADD_OPERATOR = CharacterGroup(std::vector<std::string>{"+"});
    CharacterGroup SUB_OPERATOR = CharacterGroup(std::vector<std::string>{"-"});
    CharacterGroup MUL_OPERATOR = CharacterGroup(std::vector<std::string>{"*"});
    CharacterGroup DIV_OPERATOR = CharacterGroup(std::vector<std::string>{"/"});
    CharacterGroup MOD_OPERATOR = CharacterGroup(std::vector<std::string>{"%"});

    CharacterGroup ASSIGN_OPERATOR = CharacterGroup(std::vector<std::string>{"="});
    CharacterGroup ADD_ASSIGN_OPERATOR = CharacterGroup(std::vector<std::string>{"+="});
    CharacterGroup SUB_ASSIGN_OPERATOR = CharacterGroup(std::vector<std::string>{"-="});
    CharacterGroup MUL_ASSIGN_OPERATOR = CharacterGroup(std::vector<std::string>{"*="});
    CharacterGroup DIV_ASSIGN_OPERATOR = CharacterGroup(std::vector<std::string>{"/="});
    CharacterGroup MOD_ASSIGN_OPERATOR = CharacterGroup(std::vector<std::string>{"%="});

    CharacterGroup INCREMENT_OPERATOR = CharacterGroup(std::vector<std::string>{"++"});
    CharacterGroup DECREMENT_OPERATOR = CharacterGroup(std::vector<std::string>{"--"});

    CharacterGroup NEGATE_OPERATOR = CharacterGroup(std::vector<std::string>{"-"});

    CharacterGroup NOT_OPERATOR = CharacterGroup(std::vector<std::string>{"!"});
    CharacterGroup AND_OPERATOR = CharacterGroup(std::vector<std::string>{""});
    CharacterGroup OR_OPERATOR = CharacterGroup(std::vector<std::string>{"||"});

}CharacterGroups;

CharacterGroups::CharacterGroups() {
}

CharacterGroups::~CharacterGroups() {
}
#pragma once

#include <vector>

#include "CharacterGroup.cpp"

static class CharacterGroups
{
   public:
    CharacterGroups();
    ~CharacterGroups();

    CharacterGroup WHITESPACES = CharacterGroup(std::vector<TwoChar>{' ', '\n', '\t', '\r'});

    // ------ delimitors ------

    CharacterGroup PARENTHESIS_OPEN = CharacterGroup(std::vector<TwoChar>{'('});
    CharacterGroup PARENTHESIS_CLOSE = CharacterGroup(std::vector<TwoChar>{')'});
    CharacterGroup BRACES_OPEN = CharacterGroup(std::vector<TwoChar>{'{'});
    CharacterGroup BRACES_CLOSE = CharacterGroup(std::vector<TwoChar>{'}'});
    CharacterGroup BRACKETS_OPEN = CharacterGroup(std::vector<TwoChar>{'['});
    CharacterGroup BRACKETS_CLOSE = CharacterGroup(std::vector<TwoChar>{']'});

    // ------ comments ------

    CharacterGroup SINGLE_LINE_COMMENT = CharacterGroup(std::vector<TwoChar>{TwoChar('/', '/')});
    CharacterGroup MULTI_LINE_COMMENT_START = CharacterGroup(std::vector<TwoChar>{TwoChar('/', '*')});
    CharacterGroup MULTI_LINE_COMMENT_END = CharacterGroup(std::vector<TwoChar>{TwoChar('*', '/')});

    // ------ identifiers ------

    CharacterGroup LOWER_ALPHABET =
        CharacterGroup(std::vector<TwoChar>{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                                            'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'});
    CharacterGroup UPPER_ALPHABET =
        CharacterGroup(std::vector<TwoChar>{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                                            'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'});
    CharacterGroup ALPHABET = CharacterGroup(std::vector<CharacterGroup>{LOWER_ALPHABET, UPPER_ALPHABET});

    CharacterGroup SYMBOLS = CharacterGroup(
        std::vector<TwoChar>{'.', ',', ':', ';', '+', '-', '*', '/', '%', '=', '<', '>', '&', '|', '!', '?'});

    CharacterGroup IDENTIFIER = CharacterGroup(std::vector<CharacterGroup>{ALPHABET, NUMBERS, SYMBOLS});

    // ------ consts ------

    CharacterGroup NUMBERS = CharacterGroup(std::vector<TwoChar>{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'});

    CharacterGroup STRING_DELIMITOR = CharacterGroup(std::vector<TwoChar>{'"'});

} CharacterGroups;

CharacterGroups::CharacterGroups() {}

CharacterGroups::~CharacterGroups() {}
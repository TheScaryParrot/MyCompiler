#pragma once

#include "ELookAheadCertainties.cpp"
#include "../../tokens/TokenList.cpp"

class IGrammarPattern {
public:
    static ELookAheadCertainties LookAhead(TokenList* tokens); // Looks ahead to see if the pattern is present.
    // Method Parse() is absent as it's return type is not specified.

    virtual std::string ToString() = 0; // Converts the pattern to a string.
};

ELookAheadCertainties IGrammarPattern::LookAhead(TokenList* tokens) {
    throw "IGrammarPattern::LookAhead() is abstract and shouldn't be called";
}
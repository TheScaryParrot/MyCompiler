#pragma once

#include "ELookAheadCertainties.cpp"
#include "../../tokens/TokenList.cpp"

class IGrammarPattern {
public:
    static ELookAheadCertainties LookAhead(TokenList* tokens); // Looks ahead to see if the pattern is present.
    // Method Parse() is absent as it's return type is not specified.
};
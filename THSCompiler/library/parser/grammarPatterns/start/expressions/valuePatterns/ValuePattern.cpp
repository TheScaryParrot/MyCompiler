#pragma once

#include "../../../IGrammarPattern.cpp"

#include "MutablePattern.cpp"
#include "ImmutablePattern.cpp"

#include "../../../../../tokens/ConstTokens.cpp"

class ValuePattern : public IGrammarPattern
{
public:
    ValuePattern();
    ~ValuePattern();

    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static ValuePattern* Parse(TokenList* tokens);

    virtual std::string ToString() override;

private:
    MutablePattern* mutablePattern;
    ImmutablePattern* immutablePattern;
};

ValuePattern::ValuePattern() {}

ValuePattern::~ValuePattern() {
    delete mutablePattern;
    delete immutablePattern;
}

ELookAheadCertainties ValuePattern::LookAhead(TokenList* tokens) {
    if (MutablePattern::LookAhead(tokens) == ELookAheadCertainties::CertainlyPresent || ImmutablePattern::LookAhead(tokens) == ELookAheadCertainties::CertainlyPresent) {
        return CertainlyPresent;
    }

    return CertainlyNotPresent;
}

ValuePattern* ValuePattern::Parse(TokenList* tokens) {
    ValuePattern* valuePattern = new ValuePattern();

    if (MutablePattern::LookAhead(tokens) == ELookAheadCertainties::CertainlyPresent) {
        valuePattern->mutablePattern = MutablePattern::Parse(tokens);
        return valuePattern;
    } 
    else if (ImmutablePattern::LookAhead(tokens) == ELookAheadCertainties::CertainlyPresent) {
        valuePattern->immutablePattern = ImmutablePattern::Parse(tokens);
        return valuePattern;
    } 
    
    delete valuePattern;
    throw "Error: ValuePattern::Parse: Invalid pattern. Did you forget to call LookAhead?";
}

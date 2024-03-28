#pragma once

#include "../../../IGrammarPattern.cpp"
#include "../../../../../tokens/Keywords.cpp"

class ReadWriteDeclarationPattern : public IGrammarPattern
{
public:
    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static ReadWriteDeclarationPattern* Parse(TokenList* tokens);
};

ELookAheadCertainties ReadWriteDeclarationPattern::LookAhead(TokenList* tokens)
{
    AbstractToken* nextToken =  tokens->Peek();

    if (nextToken->IsThisToken(Keywords.READ_ONLY_KEYWORD) || nextToken->IsThisToken(Keywords.CONST_KEYWORD)) {
        return ELookAheadCertainties::CertainlyPresent;
    }

    return ELookAheadCertainties::CertainlyNotPresent;
}

ReadWriteDeclarationPattern* ReadWriteDeclarationPattern::Parse(TokenList* tokens)
{
    tokens->Next(); // Consume read/write token
    //TODO: Implement
    return nullptr;
}
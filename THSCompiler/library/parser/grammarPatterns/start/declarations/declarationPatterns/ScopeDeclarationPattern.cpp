#pragma once

#include "../../../IGrammarPattern.cpp"
#include "../../../../../tokens/Keywords.cpp"

class ScopeDeclarationPattern : public IGrammarPattern
{
public:
    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static ScopeDeclarationPattern* Parse(TokenList* tokens);
};

ELookAheadCertainties ScopeDeclarationPattern::LookAhead(TokenList* tokens)
{
    AbstractToken* nextToken =  tokens->Peek();

    if (nextToken->IsThisToken(Keywords.PUBLIC_KEYWORD) || nextToken->IsThisToken(Keywords.PRIVATE_KEYWORD) || nextToken->IsThisToken(Keywords.PROTECTED_KEYWORD)) {
        return ELookAheadCertainties::CertainlyPresent;
    }

    return ELookAheadCertainties::CertainlyNotPresent;
}

ScopeDeclarationPattern* ScopeDeclarationPattern::Parse(TokenList* tokens)
{
    tokens->Next(); // Consume scope token
    // TODO: Implement
    return nullptr;
}
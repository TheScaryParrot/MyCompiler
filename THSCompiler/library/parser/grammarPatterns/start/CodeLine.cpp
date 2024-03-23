#pragma once

#include <library/parser/grammarPatterns/IGrammarPattern.cpp>
#include "declarations/DeclarationPattern.cpp"
#include "statements/StatementPattern.cpp"

class CodeLine : public IGrammarPattern
{
public:
    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static CodeLine* Parse(TokenList* tokens);

    DeclarationPattern* declaration;
    StatementPattern* statement;
};

ELookAheadCertainties CodeLine::LookAhead(TokenList* tokens)
{
    if (DeclarationPattern::LookAhead(tokens) == ELookAheadCertainties::CertainlyPresent) {
        return ELookAheadCertainties::CertainlyPresent;
    }

    if (StatementPattern::LookAhead(tokens) == ELookAheadCertainties::CertainlyPresent) {
        return ELookAheadCertainties::CertainlyPresent;
    }

    return ELookAheadCertainties::CertainlyNotPresent;
}

CodeLine* CodeLine::Parse(TokenList* tokens)
{
    CodeLine* codeLine = new CodeLine();

    if (DeclarationPattern::LookAhead(tokens) == ELookAheadCertainties::CertainlyPresent) {
        codeLine->declaration = DeclarationPattern::Parse(tokens);
        return codeLine;
    }

    if (StatementPattern::LookAhead(tokens) == ELookAheadCertainties::CertainlyPresent) {
        codeLine->statement = StatementPattern::Parse(tokens);
        return codeLine;
    }

    delete codeLine;
    return nullptr;
}
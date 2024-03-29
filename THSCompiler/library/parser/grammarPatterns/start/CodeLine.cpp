#pragma once

#include "../IGrammarPattern.cpp"
#include "declarations/DeclarationPattern.cpp"
#include "statements/StatementPattern.cpp"

class CodeLine : public IGrammarPattern
{
public:
    CodeLine();
    ~CodeLine();

    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static CodeLine* Parse(TokenList* tokens);

    virtual std::string ToString() override;

    DeclarationPattern* declaration = nullptr;
    StatementPattern* statement = nullptr;
};

CodeLine::CodeLine()
{
}

CodeLine::~CodeLine()
{
    delete declaration;
    delete statement;
}

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

std::string CodeLine::ToString()
{
    if (declaration != nullptr) {
        return declaration->ToString();
    }

    if (statement != nullptr) {
        return statement->ToString();
    }

    return "";
}
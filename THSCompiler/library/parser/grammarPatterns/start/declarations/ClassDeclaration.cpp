#pragma once

#include <typeinfo>

#include <library/parser/grammarPatterns/IGrammarPattern.cpp>

#include <library/tokens/keywords/classes/ClassKeyword.cpp>
#include <library/tokens/expressions/value/IdentifierToken.cpp>

class ClassDeclaration : public IGrammarPattern
{
public:
    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static ClassDeclaration* Parse(TokenList* tokens);

private:
    std::string className;
};

ELookAheadCertainties ClassDeclaration::LookAhead(TokenList* tokens)
{
    if (typeid(tokens->Peek(0)) != typeid(ClassKeyword)) {
        return ELookAheadCertainties::CertainlyNotPresent;
    }

    if (typeid(tokens->Peek(1)) != typeid(IdentifierToken)) {
        return ELookAheadCertainties::CertainlyNotPresent;
    }

    // BODY: Check if the class declaration is valid

    return ELookAheadCertainties::CertainlyPresent;
}

ClassDeclaration* ClassDeclaration::Parse(TokenList* tokens)
{
    ClassDeclaration* classDeclaration = new ClassDeclaration();

    tokens->Next(); // Consume class keyword
    classDeclaration->className = ((IdentifierToken*)tokens->Next())->GetValue(); // Consume identifier

    // CONSUME BODY
}
#pragma once

#include <library/parser/grammarPatterns/IGrammarPattern.cpp>

#include <library/tokens/Keywords.cpp>
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
    

    if (tokens->IsPeekOfType<ClassKeyword>(0)) {
        return ELookAheadCertainties::CertainlyPresent;
    }
    
    return ELookAheadCertainties::CertainlyNotPresent;
}

ClassDeclaration* ClassDeclaration::Parse(TokenList* tokens)
{
    ClassDeclaration* classDeclaration = new ClassDeclaration();

    tokens->Next(); // Consume class keyword
    classDeclaration->className = ((IdentifierToken*)tokens->Next())->GetValue(); // Consume identifier

    // CONSUME BODY
}
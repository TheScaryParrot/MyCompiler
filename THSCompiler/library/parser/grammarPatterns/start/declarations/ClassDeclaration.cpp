#pragma once

#include "../../IGrammarPattern.cpp"

#include "../../../../tokens/Keywords.cpp"

class ClassDeclaration : public IGrammarPattern
{
public:
    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static ClassDeclaration* Parse(TokenList* tokens);

    virtual std::string ToString() override;

private:
    std::string className;
    bool isStatic = false;
};

ELookAheadCertainties ClassDeclaration::LookAhead(TokenList* tokens)
{
    unsigned short int i = 0;

    // If the next token is static, look ahead one more token
    if (tokens->IsPeekOfTokenType(Keywords.STATIC_KEYWORD, 0)) i++;

    return tokens->IsPeekOfTokenType(Keywords.CLASS_KEYWORD, i) ? ELookAheadCertainties::CertainlyPresent : ELookAheadCertainties::CertainlyNotPresent;
}

ClassDeclaration* ClassDeclaration::Parse(TokenList* tokens)
{
    ClassDeclaration* classDeclaration = new ClassDeclaration();

    if (tokens->Next()->IsThisToken(Keywords.STATIC_KEYWORD))
    {
        classDeclaration->isStatic = true;
        tokens->Next(); // Consume class keyword
    }
    
    classDeclaration->className = ((IdentifierToken*)tokens->Next())->GetValue(); // Consume identifier

    // CONSUME BODY

    return classDeclaration;
}

std::string ClassDeclaration::ToString()
{
    if (isStatic)
        return "class definition: static " + className;

    return "class definition: " + className;
}
#pragma once

#include "../PredictiveParser.hpp"

bool PredictiveParser::LookAhead_GlobalCode(TokenList* tokens) { return LookAhead_Declaration(tokens); }
GlobalCodeNode* PredictiveParser::Parse_GlobalCode(TokenList* tokens)
{
    GlobalCodeNode* globalCodeNode = new GlobalCodeNode();

    while (LookAhead_Declaration(tokens))
    {
        globalCodeNode->AddDeclaration(Parse_Declaration(tokens));
    }

    return globalCodeNode;
}

bool PredictiveParser::LookAhead_BodyCode(TokenList* tokens) { return LookAhead_Line(tokens); }
BodyCodeNode* PredictiveParser::Parse_BodyCode(TokenList* tokens)
{
    BodyCodeNode* bodyCodeNode = new BodyCodeNode();

    while (LookAhead_Line(tokens))
    {
        bodyCodeNode->AddLine(Parse_Line(tokens));
    }

    return bodyCodeNode;
}

bool PredictiveParser::LookAhead_Line(TokenList* tokens) { return LookAhead_Declaration(tokens) || LookAhead_Statement(tokens); }
AbstractLineNode* PredictiveParser::Parse_Line(TokenList* tokens)
{
    if (LookAhead_Declaration(tokens))
    {
        return Parse_Declaration(tokens);
    }

    return Parse_Statement(tokens);
}

bool PredictiveParser::LookAhead_TypeDefCode(TokenList* tokens) { return LookAhead_PropertyDeclaration(tokens); }
TypeDefCodeNode* PredictiveParser::Parse_TypeDefCode(TokenList* tokens)
{
    TypeDefCodeNode* typeDefCodeNode = new TypeDefCodeNode();

    while (LookAhead_PropertyDeclaration(tokens))
    {
        typeDefCodeNode->AddProperty(Parse_PropertyDeclaration(tokens));
    }

    return typeDefCodeNode;
}
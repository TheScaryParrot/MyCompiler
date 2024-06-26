#pragma once

#include "../../tokens/ConstTokens.cpp"
#include "../../tokens/Keywords.cpp"
#include "../PredictiveParser.hpp"

ELookAheadCertainties PredictiveParser::LookAhead_Declaration(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(Keywords.CLASS_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;

    return LookAhead_VarFuncDeclaration(tokens);
}
AbstractDeclarationNode* PredictiveParser::Parse_Declaration(TokenList* tokens)
{
    if (LookAhead_ClassDeclaration(tokens) == ELookAheadCertainties::CertainlyPresent)
        return Parse_ClassDeclaration(tokens);
    return Parse_VarFuncDeclaration(tokens);
}

ELookAheadCertainties PredictiveParser::LookAhead_ClassDeclaration(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(Keywords.STATIC_KEYWORD))
    {
        // If static keyword is present, look at the next token
        if (tokens->IsPeekOfTokenType(Keywords.CLASS_KEYWORD, 1))
        {
            return ELookAheadCertainties::CertainlyPresent;
        }
    }
    else if (tokens->IsPeekOfTokenType(Keywords.CLASS_KEYWORD))
    {
        return ELookAheadCertainties::CertainlyPresent;
    }

    return ELookAheadCertainties::CertainlyNotPresent;
}
ClassDeclarationNode* PredictiveParser::Parse_ClassDeclaration(TokenList* tokens)
{
    // STATIC? CLASS ID BODY_OPEN <varFuncDeclaration>* BODY_CLOSE
    bool isStatic = false;
    if (tokens->IsPeekOfTokenType(Keywords.STATIC_KEYWORD))
    {
        isStatic = true;
        tokens->Next();  // Consume STATIC
    }

    tokens->Next();  // Consume CLASS

    std::string className = tokens->Next<IdentifierToken>()->GetValue();  // Consume ID

    BodyNode* body = Parse_Body(tokens);

    return new ClassDeclarationNode(isStatic, className, body);
}

ELookAheadCertainties PredictiveParser::LookAhead_VarFuncDeclaration(TokenList* tokens)
{
    // <varFuncDeclarationAttributes>
    if (LookAhead_VarFuncDeclarationAttributes(tokens) == ELookAheadCertainties::CertainlyPresent)
        return ELookAheadCertainties::CertainlyPresent;

    // VOID
    if (tokens->IsPeekOfTokenType(Keywords.VOID_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;

    // ID ID
    if (tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN) &&
        tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN, 1))
        return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
AbstractVarFuncDeclarationNode* PredictiveParser::Parse_VarFuncDeclaration(TokenList* tokens)
{
    if (LookAhead_FuncDeclaration(tokens) == ELookAheadCertainties::CertainlyPresent)
        return Parse_FuncDeclaration(tokens);
    return Parse_VarDeclaration(tokens);
}

ELookAheadCertainties PredictiveParser::LookAhead_VarDeclaration(TokenList* tokens)
{
    unsigned int i = Skip_VarFuncDeclarationAttributes(tokens);

    // <varFuncDeclarationAttributes>? ID ID !(
    if (!tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN, i++))
        return ELookAheadCertainties::CertainlyNotPresent;
    if (!tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN, i++))
        return ELookAheadCertainties::CertainlyNotPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.PARENTHESIS_OPEN_TOKEN, i))
        return ELookAheadCertainties::CertainlyNotPresent;

    return ELookAheadCertainties::CertainlyPresent;
}
VarDeclarationNode* PredictiveParser::Parse_VarDeclaration(TokenList* tokens)
{
    SyntaxTreeDeclarationAttributes attributes = Parse_VarFuncDeclarationAttributes(tokens);
    TypeNode type = TypeNode(tokens->Next<IdentifierToken>()->GetValue());
    std::string name = tokens->Next<IdentifierToken>()->GetValue();
    AbstractExpressionNode* value = nullptr;

    if (tokens->IsPeekOfTokenType(ConstTokens.ASSIGN_OPERATOR_TOKEN))
    {
        tokens->Next();  // Consume ASSIGN_OPERATOR
        value = Parse_Expression(tokens);
    }

    tokens->Next();  // Consume STATEMENT_END

    return new VarDeclarationNode(attributes, type, name, value);
}

ELookAheadCertainties PredictiveParser::LookAhead_FuncDeclaration(TokenList* tokens)
{
    unsigned int i = Skip_VarFuncDeclarationAttributes(tokens);

    // <varFuncDeclarationAttributes>? VOID
    if (tokens->IsPeekOfTokenType(Keywords.VOID_KEYWORD, i)) return ELookAheadCertainties::CertainlyPresent;

    // <varFuncDeclarationAttributes>? ID ID (
    if (!tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN, i++))
        return ELookAheadCertainties::CertainlyNotPresent;
    if (!tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN, i++))
        return ELookAheadCertainties::CertainlyNotPresent;
    if (!tokens->IsPeekOfTokenType(ConstTokens.PARENTHESIS_OPEN_TOKEN, i))
        return ELookAheadCertainties::CertainlyNotPresent;

    return ELookAheadCertainties::CertainlyPresent;
}
FuncDeclarationNode* PredictiveParser::Parse_FuncDeclaration(TokenList* tokens)
{
    SyntaxTreeDeclarationAttributes attributes = Parse_VarFuncDeclarationAttributes(tokens);
    FunctionReturnTypeNode returnType;

    if (tokens->IsPeekOfTokenType(Keywords.VOID_KEYWORD))
    {
        tokens->Next();  // Consume VOID
        returnType = FunctionReturnTypeNode("void");
    }
    else
    {
        returnType = FunctionReturnTypeNode(tokens->Next<IdentifierToken>()->GetValue());
    }

    std::string name = tokens->Next<IdentifierToken>()->GetValue();

    tokens->Next();  // Consume PARENTHESIS_OPEN

    std::vector<ParameterDeclarationNode*>* parameters = Parse_Params(tokens);

    tokens->Next();  // Consume PARENTHESIS_CLOSE

    BodyNode* body = Parse_Body(tokens);

    return new FuncDeclarationNode(attributes, returnType, name, parameters, body);
}

ELookAheadCertainties PredictiveParser::LookAhead_VarFuncDeclarationAttributes(TokenList* tokens, unsigned int offset)
{
    // <scope> | <static> | <readWrite>
    if (LookAhead_ScopeAttribute(tokens, offset) == ELookAheadCertainties::CertainlyPresent)
        return ELookAheadCertainties::CertainlyPresent;
    if (LookAhead_StaticAttribute(tokens, offset) == ELookAheadCertainties::CertainlyPresent)
        return ELookAheadCertainties::CertainlyPresent;
    if (LookAhead_FinalAttribute(tokens, offset) == ELookAheadCertainties::CertainlyPresent)
        return ELookAheadCertainties::CertainlyPresent;
    if (LookAhead_InlineAttribute(tokens, offset) == ELookAheadCertainties::CertainlyPresent)
        return ELookAheadCertainties::CertainlyPresent;

    // no attributes case
    return ELookAheadCertainties::Unknown;
}
unsigned int PredictiveParser::Skip_VarFuncDeclarationAttributes(TokenList* tokens)
{
    unsigned int skippedTokens = 0;

    // while either scope, static or readwrite attribute is present. If empty this will be
    // ELookAheadCertainties::Unknown
    while (LookAhead_VarFuncDeclarationAttributes(tokens, skippedTokens) == ELookAheadCertainties::CertainlyPresent)
    {
        skippedTokens++;
    }

    return skippedTokens;
}
SyntaxTreeDeclarationAttributes PredictiveParser::Parse_VarFuncDeclarationAttributes(TokenList* tokens)
{
    SyntaxTreeDeclarationAttributes attributes;

    if (LookAhead_ScopeAttribute(tokens) == ELookAheadCertainties::CertainlyPresent)
    {
        attributes.scope = Parse_ScopeAttribute(tokens);
    }

    if (LookAhead_StaticAttribute(tokens) == ELookAheadCertainties::CertainlyPresent)
    {
        attributes.isStatic = Parse_StaticAttribute(tokens);
    }

    if (LookAhead_FinalAttribute(tokens) == ELookAheadCertainties::CertainlyPresent)
    {
        attributes.isFinal = Parse_FinalAttribute(tokens);
    }

    if (LookAhead_InlineAttribute(tokens) == ELookAheadCertainties::CertainlyPresent)
    {
        attributes.isInline = Parse_InlineAttribute(tokens);
    }

    return attributes;
}

ELookAheadCertainties PredictiveParser::LookAhead_Params(TokenList* tokens)
{
    // <paramDeclaration> (SEPERATOR <paramDeclaration>)* can be empty, therefore always unknown
    return ELookAheadCertainties::Unknown;
}
std::vector<ParameterDeclarationNode*>* PredictiveParser::Parse_Params(TokenList* tokens)
{
    std::vector<ParameterDeclarationNode*>* parameters = new std::vector<ParameterDeclarationNode*>();

    if (LookAhead_ParamDeclaration(tokens) != ELookAheadCertainties::CertainlyPresent)
    {
        return parameters;
    }

    parameters->push_back(Parse_ParamDeclaration(tokens));  // Parse first parameter

    // (SEPERATOR <paramDeclaration>)*
    while (tokens->IsPeekOfTokenType(ConstTokens.SEPERATOR_TOKEN))
    {
        tokens->Next();                                         // Consume seperator
        parameters->push_back(Parse_ParamDeclaration(tokens));  // Parse next parameter
    }

    return parameters;
}

ELookAheadCertainties PredictiveParser::LookAhead_ParamDeclaration(TokenList* tokens)
{
    // ID ID
    if (tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN) &&
        tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN, 1))
        return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
ParameterDeclarationNode* PredictiveParser::Parse_ParamDeclaration(TokenList* tokens)
{
    std::string type = tokens->Next<IdentifierToken>()->GetValue();
    return new ParameterDeclarationNode(type, tokens->Next<IdentifierToken>()->GetValue());
}

ELookAheadCertainties PredictiveParser::LookAhead_Body(TokenList* tokens)
{
    // BODY_OPEN
    if (tokens->IsPeekOfTokenType(ConstTokens.BODY_OPEN_TOKEN)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
BodyNode* PredictiveParser::Parse_Body(TokenList* tokens)
{
    BodyNode* bodynode = new BodyNode();

    tokens->Next();  // Consume BODY_OPEN

    while (!tokens->IsPeekOfTokenType(ConstTokens.BODY_CLOSE_TOKEN))
    {
        bodynode->AddCodeLine(Parse_Line(tokens));
    }

    tokens->Next();  // Consume BODY_CLOSE

    return bodynode;
}

ELookAheadCertainties PredictiveParser::LookAhead_ScopeAttribute(TokenList* tokens, unsigned int offset)
{
    // PUBLIC | PRIVATE | PROTECTED
    if (tokens->IsPeekOfTokenType(Keywords.PUBLIC_KEYWORD, offset) ||
        tokens->IsPeekOfTokenType(Keywords.PRIVATE_KEYWORD, offset) ||
        tokens->IsPeekOfTokenType(Keywords.PROTECTED_KEYWORD, offset))
        return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
ESyntaxTreeScopes PredictiveParser::Parse_ScopeAttribute(TokenList* tokens)
{
    std::shared_ptr<AbstractToken> nextToken = tokens->Next();  // Consume scope keyword

    if (nextToken->IsThisToken(Keywords.PUBLIC_KEYWORD)) return ESyntaxTreeScopes::PUBLIC;

    if (nextToken->IsThisToken(Keywords.PRIVATE_KEYWORD)) return ESyntaxTreeScopes::PRIVATE;

    return ESyntaxTreeScopes::PROTECTED;
}

ELookAheadCertainties PredictiveParser::LookAhead_StaticAttribute(TokenList* tokens, unsigned int offset)
{
    // STATIC
    if (tokens->IsPeekOfTokenType(Keywords.STATIC_KEYWORD, offset)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
bool PredictiveParser::Parse_StaticAttribute(TokenList* tokens)
{
    tokens->Next();  // Constume STATIC
    return true;  // As LookAhead_StaticAttribute() has returned CertainlyPresent, we know that static must be present
}

ELookAheadCertainties PredictiveParser::LookAhead_FinalAttribute(TokenList* tokens, unsigned int offset)
{
    // FINAL
    if (tokens->IsPeekOfTokenType(Keywords.FINAL_KEYWORD, offset)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
bool PredictiveParser::Parse_FinalAttribute(TokenList* tokens)
{
    tokens->Next();  // Consume FINAL
    return true;     // As LookAhead_FinalAttribute() has returned CertainlyPresent, we know that final must be present
}

ELookAheadCertainties PredictiveParser::LookAhead_InlineAttribute(TokenList* tokens, unsigned int offset)
{
    // INLINE
    if (tokens->IsPeekOfTokenType(Keywords.INLINE_KEYWORD, offset)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
bool PredictiveParser::Parse_InlineAttribute(TokenList* tokens)
{
    tokens->Next();  // Consume INLINE
    return true;  // As LookAhead_InlineAttribute() has returned CertainlyPresent, we know that inline must be present
}

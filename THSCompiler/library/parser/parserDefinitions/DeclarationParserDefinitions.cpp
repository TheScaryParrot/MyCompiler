#pragma once

#include "../../tokens/ConstTokens.cpp"
#include "../../tokens/Keywords.cpp"
#include "../PredictiveParser.hpp"

bool PredictiveParser::LookAhead_Declaration(TokenList* tokens)
{
    return tokens->IsPeekOfTokenType(Keywords.CLASS_KEYWORD) || LookAhead_VarFuncDeclaration(tokens);
}
AbstractDeclarationNode* PredictiveParser::Parse_Declaration(TokenList* tokens)
{
    if (LookAhead_ClassDeclaration(tokens)) return Parse_ClassDeclaration(tokens);
    return Parse_VarFuncDeclaration(tokens);
}

bool PredictiveParser::LookAhead_ClassDeclaration(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(Keywords.STATIC_KEYWORD))
    {
        // If static keyword is present, look at the next token
        return tokens->IsPeekOfTokenType(Keywords.CLASS_KEYWORD, 1);
    }

    return tokens->IsPeekOfTokenType(Keywords.CLASS_KEYWORD);
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

bool PredictiveParser::LookAhead_VarFuncDeclaration(TokenList* tokens)
{
    return LookAhead_VarDeclaration(tokens) || LookAhead_FuncDeclaration(tokens);
}
AbstractVarFuncDeclarationNode* PredictiveParser::Parse_VarFuncDeclaration(TokenList* tokens)
{
    if (LookAhead_FuncDeclaration(tokens) == true) return Parse_FuncDeclaration(tokens);
    return Parse_VarDeclaration(tokens);
}

bool PredictiveParser::LookAhead_VarDeclaration(TokenList* tokens)
{
    unsigned int i = Skip_VarFuncDeclarationAttributes(tokens);

    // <varFuncDeclarationAttributes>? ID ID !(
    return tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN, i++) &&  // ID
           tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN, i++) &&  // ID
           !tokens->IsPeekOfTokenType(ConstTokens.PARENTHESIS_OPEN_TOKEN, i);     // !(
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

bool PredictiveParser::LookAhead_FuncDeclaration(TokenList* tokens)
{
    unsigned int i = Skip_VarFuncDeclarationAttributes(tokens);

    // <varFuncDeclarationAttributes>? VOID
    if (tokens->IsPeekOfTokenType(Keywords.VOID_KEYWORD, i)) return true;

    // <varFuncDeclarationAttributes>? ID ID (
    return tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN, i++) &&  // ID
           tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN, i++) &&  // ID
           tokens->IsPeekOfTokenType(ConstTokens.PARENTHESIS_OPEN_TOKEN, i);      // (
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

bool PredictiveParser::LookAhead_VarFuncDeclarationAttributes(TokenList* tokens, unsigned int offset)
{
    // <scope> | <static> | <final> | <inline>
    return LookAhead_ScopeAttribute(tokens, offset) || LookAhead_StaticAttribute(tokens, offset) || LookAhead_FinalAttribute(tokens, offset) ||
           LookAhead_InlineAttribute(tokens, offset);
}
unsigned int PredictiveParser::Skip_VarFuncDeclarationAttributes(TokenList* tokens)
{
    unsigned int skippedTokens = 0;

    // while either scope, static or readwrite attribute is present. If empty this will be false
    while (LookAhead_VarFuncDeclarationAttributes(tokens, skippedTokens))
    {
        skippedTokens++;
    }

    return skippedTokens;
}
SyntaxTreeDeclarationAttributes PredictiveParser::Parse_VarFuncDeclarationAttributes(TokenList* tokens)
{
    SyntaxTreeDeclarationAttributes attributes;

    if (LookAhead_ScopeAttribute(tokens))
    {
        attributes.scope = Parse_ScopeAttribute(tokens);
    }

    if (LookAhead_StaticAttribute(tokens))
    {
        attributes.isStatic = Parse_StaticAttribute(tokens);
    }

    if (LookAhead_FinalAttribute(tokens))
    {
        attributes.isFinal = Parse_FinalAttribute(tokens);
    }

    if (LookAhead_InlineAttribute(tokens))
    {
        attributes.isInline = Parse_InlineAttribute(tokens);
    }

    return attributes;
}

bool PredictiveParser::LookAhead_Params(TokenList* tokens)
{
    // <paramDeclaration> (SEPERATOR <paramDeclaration>)* can be empty, therefore always true
    return true;
}
std::vector<ParameterDeclarationNode*>* PredictiveParser::Parse_Params(TokenList* tokens)
{
    std::vector<ParameterDeclarationNode*>* parameters = new std::vector<ParameterDeclarationNode*>();

    if (LookAhead_ParamDeclaration(tokens) != true)
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

bool PredictiveParser::LookAhead_ParamDeclaration(TokenList* tokens)
{
    // <paramAttributes> | ID ID
    if (tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN) && tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN, 1))
        return true;

    return LookAhead_ParamAttributes(tokens);
}
ParameterDeclarationNode* PredictiveParser::Parse_ParamDeclaration(TokenList* tokens)
{
    SyntaxTreeParamAttributes attributes;

    if (LookAhead_ParamAttributes(tokens) == true)
    {
        attributes = Parse_ParamAttributes(tokens);
    }

    std::string type = tokens->Next<IdentifierToken>()->GetValue();

    return new ParameterDeclarationNode(attributes, type, tokens->Next<IdentifierToken>()->GetValue());
}

bool PredictiveParser::LookAhead_ParamAttributes(TokenList* tokens)
{
    // FINAL | INLINE
    return LookAhead_FinalAttribute(tokens) || LookAhead_InlineAttribute(tokens);
}
SyntaxTreeParamAttributes PredictiveParser::Parse_ParamAttributes(TokenList* tokens)
{
    SyntaxTreeParamAttributes attributes;

    if (LookAhead_FinalAttribute(tokens) == true)
    {
        attributes.isFinal = Parse_FinalAttribute(tokens);
    }

    if (LookAhead_InlineAttribute(tokens) == true)
    {
        attributes.isInline = Parse_InlineAttribute(tokens);
    }

    return attributes;
}

bool PredictiveParser::LookAhead_Body(TokenList* tokens)
{
    // BODY_OPEN
    return tokens->IsPeekOfTokenType(ConstTokens.BODY_OPEN_TOKEN);
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

bool PredictiveParser::LookAhead_ScopeAttribute(TokenList* tokens, unsigned int offset)
{
    // PUBLIC | PRIVATE | PROTECTED
    return tokens->IsPeekOfTokenType(Keywords.PUBLIC_KEYWORD, offset) || tokens->IsPeekOfTokenType(Keywords.PRIVATE_KEYWORD, offset) ||
           tokens->IsPeekOfTokenType(Keywords.PROTECTED_KEYWORD, offset);
}
ESyntaxTreeScopes PredictiveParser::Parse_ScopeAttribute(TokenList* tokens)
{
    std::shared_ptr<Token> nextToken = tokens->Next();  // Consume scope keyword

    if (nextToken->IsThisToken(Keywords.PUBLIC_KEYWORD)) return ESyntaxTreeScopes::PUBLIC;

    if (nextToken->IsThisToken(Keywords.PRIVATE_KEYWORD)) return ESyntaxTreeScopes::PRIVATE;

    return ESyntaxTreeScopes::PROTECTED;
}

bool PredictiveParser::LookAhead_StaticAttribute(TokenList* tokens, unsigned int offset)
{
    // STATIC
    return tokens->IsPeekOfTokenType(Keywords.STATIC_KEYWORD, offset);
}
bool PredictiveParser::Parse_StaticAttribute(TokenList* tokens)
{
    tokens->Next();  // Constume STATIC
    return true;     // As LookAhead_StaticAttribute() has returned CertainlyPresent, we know that static must be present
}

bool PredictiveParser::LookAhead_FinalAttribute(TokenList* tokens, unsigned int offset)
{
    // FINAL
    return tokens->IsPeekOfTokenType(Keywords.FINAL_KEYWORD, offset);
}
bool PredictiveParser::Parse_FinalAttribute(TokenList* tokens)
{
    tokens->Next();  // Consume FINAL
    return true;     // As LookAhead_FinalAttribute() has returned CertainlyPresent, we know that final must be present
}

bool PredictiveParser::LookAhead_InlineAttribute(TokenList* tokens, unsigned int offset)
{
    // INLINE
    return tokens->IsPeekOfTokenType(Keywords.INLINE_KEYWORD, offset);
}
bool PredictiveParser::Parse_InlineAttribute(TokenList* tokens)
{
    tokens->Next();  // Consume INLINE
    return true;     // As LookAhead_InlineAttribute() has returned CertainlyPresent, we know that inline must be present
}

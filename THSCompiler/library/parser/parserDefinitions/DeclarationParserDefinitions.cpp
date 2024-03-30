#pragma once

#include "../PredictiveParser.hpp"

#include "../../tokens/ConstTokens.cpp"
#include "../../tokens/Keywords.cpp"

ELookAheadCertainties PredictiveParser::LookAhead_Declaration(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(Keywords.CLASS_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;

    return LookAhead_VarFuncDeclaration(tokens);
}
AbstractDeclarationNode* PredictiveParser::Parse_Declaration(TokenList* tokens)
{
    if (LookAhead_ClassDeclaration(tokens) == ELookAheadCertainties::CertainlyPresent) return Parse_ClassDeclaration(tokens);
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
ClassDeclarationNode* PredictiveParser::Parse_ClassDeclaration(TokenList* tokens /*, Node*/)
{
    // STATIC? CLASS ID BODY_OPEN <varFuncDeclaration>* BODY_CLOSE
    bool isStatic = false;
    if (tokens->IsPeekOfTokenType(Keywords.STATIC_KEYWORD))
    {
        isStatic = true;
        tokens->Next(); // Consume STATIC
    }

    tokens->Next(); // Consume CLASS

    std::string className = tokens->Next<IdentifierToken>()->GetValue();

    // TODO: Handle Body

    return new ClassDeclarationNode(isStatic, className);
}

ELookAheadCertainties PredictiveParser::LookAhead_VarFuncDeclaration(TokenList* tokens)
{
    // <varFuncDeclarationAttributes>
    if (LookAhead_VarFuncDeclarationAttributes(tokens) == ELookAheadCertainties::CertainlyPresent) return ELookAheadCertainties::CertainlyPresent;

    // VOID
    if (tokens->IsPeekOfTokenType(Keywords.VOID_KEYWORD))return ELookAheadCertainties::CertainlyPresent; 

    // ID ID
    if (tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN) && tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN, 1)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
AbstractVarFuncDeclarationNode* PredictiveParser::Parse_VarFuncDeclaration(TokenList* tokens /*, Node*/)
{
    if (LookAhead_FuncDeclaration(tokens) == ELookAheadCertainties::CertainlyPresent) return Parse_FuncDeclaration(tokens);
    return Parse_VarDeclaration(tokens);
}

ELookAheadCertainties PredictiveParser::LookAhead_VarDeclaration(TokenList* tokens)
{
    unsigned int i = Skip_VarFuncDeclarationAttributes(tokens);

    // <varFuncDeclarationAttributes>? ID ID !(
    if (!tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN, i++)) return ELookAheadCertainties::CertainlyNotPresent;
    if (!tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN, i++)) return ELookAheadCertainties::CertainlyNotPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.PARENTHESIS_OPEN_TOKEN, i)) return ELookAheadCertainties::CertainlyNotPresent;

    return ELookAheadCertainties::CertainlyPresent;
}
VarDeclarationNode* PredictiveParser::Parse_VarDeclaration(TokenList* tokens /*, Node*/)
{
    DeclarationAttributes attributes = Parse_VarFuncDeclarationAttributes(tokens);
    TypeNode type = TypeNode(tokens->Next<IdentifierToken>()->GetValue());
    std::string name = tokens->Next<IdentifierToken>()->GetValue();
    // TODO Implement value assign

    return new VarDeclarationNode(attributes, type, name);
}

ELookAheadCertainties PredictiveParser::LookAhead_FuncDeclaration(TokenList* tokens)
{
    unsigned int i = Skip_VarFuncDeclarationAttributes(tokens);

    // <varFuncDeclarationAttributes>? VOID
    if (tokens->IsPeekOfTokenType(Keywords.VOID_KEYWORD, i)) return ELookAheadCertainties::CertainlyPresent;

    // <varFuncDeclarationAttributes>? ID ID (
    if (!tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN, i++)) return ELookAheadCertainties::CertainlyNotPresent;
    if (!tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN, i++)) return ELookAheadCertainties::CertainlyNotPresent;
    if (!tokens->IsPeekOfTokenType(ConstTokens.PARENTHESIS_OPEN_TOKEN, i)) return ELookAheadCertainties::CertainlyNotPresent;

    return ELookAheadCertainties::CertainlyPresent;
}
FuncDeclarationNode* PredictiveParser::Parse_FuncDeclaration(TokenList* tokens /*, Node*/)
{
    DeclarationAttributes attributes = Parse_VarFuncDeclarationAttributes(tokens);
    FunctionReturnTypeNode returnType = FunctionReturnTypeNode(tokens->Next<IdentifierToken>()->GetValue());
    std::string name = tokens->Next<IdentifierToken>()->GetValue();
    std::vector<ParameterDeclarationNode*>* parameters = Parse_Params(tokens);

    // TODO Handle Body

    return new FuncDeclarationNode(attributes, returnType, name, parameters);
}

ELookAheadCertainties PredictiveParser::LookAhead_VarFuncDeclarationAttributes(TokenList* tokens)
{
    // <scope> | <static> | <readWrite>
    if (LookAhead_ScopeAttribute(tokens) == ELookAheadCertainties::CertainlyPresent) return ELookAheadCertainties::CertainlyPresent;
    if (LookAhead_StaticAttribute(tokens) == ELookAheadCertainties::CertainlyPresent) return ELookAheadCertainties::CertainlyPresent;
    if (LookAhead_ReadWriteAttribute(tokens) == ELookAheadCertainties::CertainlyPresent) return ELookAheadCertainties::CertainlyPresent;

    // no attributes case
    return ELookAheadCertainties::Unknown;
}
unsigned int PredictiveParser::Skip_VarFuncDeclarationAttributes(TokenList* tokens)
{
    unsigned int skippedTokens = 0;

    // while either scope, static or readwrite attribute is present. If empty this will be ELookAheadCertainties::Unknown
    while (LookAhead_VarFuncDeclarationAttributes(tokens) == ELookAheadCertainties::CertainlyPresent)
    {
        skippedTokens++;
    }

    return skippedTokens;
}
DeclarationAttributes PredictiveParser::Parse_VarFuncDeclarationAttributes(TokenList* tokens /*, Node*/)
{
    DeclarationAttributes attributes;

    unsigned int i = 0;

    if (LookAhead_ScopeAttribute(tokens) == ELookAheadCertainties::CertainlyPresent)
    {
        attributes.scope = Parse_ScopeAttribute(tokens);
        i++;
    }

    if (LookAhead_StaticAttribute(tokens) == ELookAheadCertainties::CertainlyPresent)
    {
        attributes.isStatic = Parse_StaticAttribute(tokens);
        i++;
    }

    if (LookAhead_ReadWriteAttribute(tokens) == ELookAheadCertainties::CertainlyPresent)
    {
        attributes.readWrite = Parse_ReadWriteAttribute(tokens);
        i++;
    }

    return attributes;
}

ELookAheadCertainties PredictiveParser::LookAhead_Params(TokenList* tokens)
{
    // <paramDeclaration> (SEPERATOR <paramDeclaration>)* can be empty, therefore always unknown
    return ELookAheadCertainties::Unknown;
}
std::vector<ParameterDeclarationNode*>* PredictiveParser::Parse_Params(TokenList* tokens /*, Node*/)
{
    std::vector<ParameterDeclarationNode*>* parameters = new std::vector<ParameterDeclarationNode*>();

    if (LookAhead_ParamDeclaration(tokens) != ELookAheadCertainties::CertainlyPresent)
    {
        return parameters;
    }

    parameters->push_back(Parse_ParamDeclaration(tokens)); // Parse first parameter

    // (SEPERATOR <paramDeclaration>)*
    while (tokens->IsPeekOfTokenType(ConstTokens.SEPERATOR_TOKEN))
    {
        tokens->Next(); // Consume seperator
        parameters->push_back(Parse_ParamDeclaration(tokens)); // Parse next parameter
    }

    return parameters;
}

ELookAheadCertainties PredictiveParser::LookAhead_ParamDeclaration(TokenList* tokens)
{
    // ID ID
    if (tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN) && tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN, 1)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
ParameterDeclarationNode* PredictiveParser::Parse_ParamDeclaration(TokenList* tokens /*, Node*/)
{
    // TODO Implement type
    return new ParameterDeclarationNode(tokens->Next<IdentifierToken>()->GetValue());
}

ELookAheadCertainties PredictiveParser::LookAhead_Body(TokenList* tokens)
{
    // BODY_OPEN
    if (tokens->IsPeekOfTokenType(ConstTokens.BODY_OPEN_TOKEN)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
void PredictiveParser::Parse_Body(TokenList* tokens /*, Node*/)
{
}

ELookAheadCertainties PredictiveParser::LookAhead_ScopeAttribute(TokenList* tokens)
{
    // PUBLIC | PRIVATE | PROTECTED
    if (tokens->IsPeekOfTokenType(Keywords.PUBLIC_KEYWORD) || tokens->IsPeekOfTokenType(Keywords.PRIVATE_KEYWORD) || tokens->IsPeekOfTokenType(Keywords.PROTECTED_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
EScopes PredictiveParser::Parse_ScopeAttribute(TokenList* tokens /*, Node*/)
{
}

ELookAheadCertainties PredictiveParser::LookAhead_StaticAttribute(TokenList* tokens)
{
    // STATIC
    if (tokens->IsPeekOfTokenType(Keywords.STATIC_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
bool PredictiveParser::Parse_StaticAttribute(TokenList* tokens /*, Node*/)
{
}

ELookAheadCertainties PredictiveParser::LookAhead_ReadWriteAttribute(TokenList* tokens)
{
    // READ | WRITE
    if (tokens->IsPeekOfTokenType(Keywords.READ_ONLY_KEYWORD) || tokens->IsPeekOfTokenType(Keywords.CONST_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
EReadWrites PredictiveParser::Parse_ReadWriteAttribute(TokenList* tokens /*, Node*/)
{
}

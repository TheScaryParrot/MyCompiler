#include "../../tokens/TokenWithValue.cpp"
#include "../../tokens/Tokens.cpp"
#include "../PredictiveParser.hpp"

bool PredictiveParser::LookAhead_CompilerInstruction(TokenList* tokens)
{
    if (tokens->Peek() == nullptr) return false;

    return tokens->Peek()->IsCompilerInstruction();
}
AbstractCompilerInstructionNode* PredictiveParser::Parse_CompilerInstruction(TokenList* tokens)
{
    Token* token = tokens->Next();  // Consume compiler instruction

    if (token->IsThisToken(Tokens.EXTERN_INSTRUCTION)) return Parse_ExternInstruction(tokens);

    if (token->IsThisToken(Tokens.GLOBAL_INSTRUCTION)) return Parse_GlobalInstruction(tokens);

    Logger.Log("Unknown compiler instruction: " + token->ToString(), Logger::ERROR);
    return nullptr;
}

bool PredictiveParser::LookAhead_ExternInstruction(TokenList* tokens) { return tokens->Peek()->IsThisToken(Tokens.EXTERN_INSTRUCTION); }
ExternInstructionNode* PredictiveParser::Parse_ExternInstruction(TokenList* tokens)
{
    FunctionReturnTypeNode returnType = Parse_FunctionReturnType(tokens);

    std::string identifier = tokens->Next<TokenWithValue>()->GetValue();

    tokens->Next();  // Consume OPEN_PARENTHESIS_TOKEN

    std::vector<ParameterDeclarationNode*>* parameters = Parse_Params(tokens);

    tokens->Next();  // Consume CLOSE_PARENTHESIS_TOKEN
    tokens->Next();  // Consume STATEMENT_END_TOKEN

    return new ExternInstructionNode(returnType, identifier, parameters);
}

bool PredictiveParser::LookAhead_GlobalInstruction(TokenList* tokens) { return tokens->Peek()->IsThisToken(Tokens.GLOBAL_INSTRUCTION); }
GlobalInstructionNode* PredictiveParser::Parse_GlobalInstruction(TokenList* tokens)
{
    std::string identifier = tokens->Next<TokenWithValue>()->GetValue();
    tokens->Next();  // Consume STATEMENT_END_TOKEN

    return new GlobalInstructionNode(identifier);
}
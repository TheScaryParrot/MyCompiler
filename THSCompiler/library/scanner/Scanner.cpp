#pragma once

#include <iostream>

#include "../InputFile.cpp"
#include "../tokens/CharacterGroupToken.cpp"
#include "../tokens/TokenList.cpp"
#include "../tokens/TokenWithValue.cpp"
#include "../tokens/Tokens.cpp"
#include "../tokens/characterGroups/CharacterGroups.cpp"

static class Scanner
{
   private:
    bool TryAddCharacterGroupToken(InputFile* file, TokenList* tokens, CharacterGroupToken& token, char consumedCharacter, char peekCharacter)
    {
        unsigned int match = token.Match(consumedCharacter, peekCharacter);

        if (match == 0) return false;

        tokens->AddToken(token.New(lineCounter));

        if (match == 2) file->ReadNext();  // As the peek character matched aswell we need to consume it

        return true;
    }

    bool TryAddKeywordToken(TokenList* tokens, std::string keyword, KeywordToken& token)
    {
        if (token.IsThisKeyword(keyword))
        {
            tokens->AddToken(token.New(lineCounter));
            return true;
        }

        return false;
    }

    bool TryAddKeyword(TokenList* tokens, std::string keyword)
    {
        if (TryAddKeywordToken(tokens, keyword, Tokens.IF_KEYWORD)) return true;
        if (TryAddKeywordToken(tokens, keyword, Tokens.ELSE_KEYWORD)) return true;
        if (TryAddKeywordToken(tokens, keyword, Tokens.ELIF_KEYWORD)) return true;

        if (TryAddKeywordToken(tokens, keyword, Tokens.WHILE_KEYWORD)) return true;
        if (TryAddKeywordToken(tokens, keyword, Tokens.FOR_KEYWORD)) return true;
        if (TryAddKeywordToken(tokens, keyword, Tokens.BREAK_KEYWORD)) return true;
        if (TryAddKeywordToken(tokens, keyword, Tokens.CONTINUE_KEYWORD)) return true;

        if (TryAddKeywordToken(tokens, keyword, Tokens.LOGICAL_TRUE_KEYWORD)) return true;
        if (TryAddKeywordToken(tokens, keyword, Tokens.LOGICAL_FALSE_KEYWORD)) return true;

        if (TryAddKeywordToken(tokens, keyword, Tokens.RETURN_KEYWORD)) return true;
        if (TryAddKeywordToken(tokens, keyword, Tokens.VOID_KEYWORD)) return true;

        if (TryAddKeywordToken(tokens, keyword, Tokens.FINAL_KEYWORD)) return true;
        if (TryAddKeywordToken(tokens, keyword, Tokens.INLINE_KEYWORD)) return true;

        if (TryAddKeywordToken(tokens, keyword, Tokens.TYPEDEF_KEYWORD)) return true;

        return false;
    }

    bool TryAddCompilerInstructionToken(TokenList* tokens, std::string instruction, CompilerInstructionToken& token)
    {
        if (token.IsThisInstruction(instruction))
        {
            tokens->AddToken(token.New(lineCounter));
            return true;
        }

        return false;
    }

    bool TryAddCompilerInstruction(TokenList* tokens, std::string instruction)
    {
        if (TryAddCompilerInstructionToken(tokens, instruction, Tokens.EXTERN_INSTRUCTION)) return true;
        if (TryAddCompilerInstructionToken(tokens, instruction, Tokens.GLOBAL_INSTRUCTION)) return true;

        return false;
    }

    unsigned int lineCounter = 1;

   public:
    TokenList* Scan(InputFile* file)
    {
        TokenList* tokens = new TokenList();

        if (!file->IsGood())
        {
            throw "Can't scan InputFile. file is not good";
        }

        while (!file->IsEndOfFile())
        {
            char character = file->ReadNext();
            char peekCharacter = file->PeekNext();

            // used for caching the last result of a CharacterGroup::Match() call
            unsigned int match = 0;

            if (CharacterGroups.NEWLINE.Match(character, peekCharacter))
            {
                lineCounter++;
                continue;
            }

            // Ignore whitespaces
            if (CharacterGroups.WHITESPACES.Match(character, peekCharacter)) continue;

            // --- Delimitors ---
            if (TryAddCharacterGroupToken(file, tokens, Tokens.STATEMENT_END_TOKEN, character, peekCharacter)) continue;

            if (TryAddCharacterGroupToken(file, tokens, Tokens.BRACES_OPEN_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.BRACES_CLOSE_TOKEN, character, peekCharacter)) continue;

            if (TryAddCharacterGroupToken(file, tokens, Tokens.PARENTHESIS_OPEN_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.PARENTHESIS_CLOSE_TOKEN, character, peekCharacter)) continue;

            if (TryAddCharacterGroupToken(file, tokens, Tokens.SEPERATOR_TOKEN, character, peekCharacter)) continue;

            // --- Comments ---
            if (CharacterGroups.SINGLE_LINE_COMMENT.Match(character, peekCharacter))
            {
                while (file->PeekNext() != '\n')
                {
                    file->ReadNext();
                }

                continue;
            }

            match = CharacterGroups.MULTI_LINE_COMMENT_START.Match(character, peekCharacter);

            if (match)
            {
                if (match == 2) file->ReadNext();

                match = CharacterGroups.MULTI_LINE_COMMENT_END.Match(character, file->PeekNext());

                while (!match)
                {
                    character = file->ReadNext();
                    match = CharacterGroups.MULTI_LINE_COMMENT_END.Match(character, file->PeekNext());
                }

                // If multi line comment end is two characters long we need to consume the second character
                if (match == 2) file->ReadNext();

                continue;
            }

            // --- Number ---
            if (CharacterGroups.NUMBERS.Match(character, peekCharacter))
            {
                std::string number = std::string(1, character);

                bool foundDot = false;

                while (CharacterGroups.NUMBER_OR_DOT.Match(file->PeekNext(),
                                                           0))  // INFO: It's a bit of a hack to pass 0 as the second argument; but should work
                {
                    if (file->PeekNext() == '.')
                    {
                        if (foundDot)
                        {
                            std::cerr << "Invalid number format. Multiple dots in number\n";
                            break;
                        }

                        foundDot = true;
                    }

                    number += file->ReadNext();
                }

                if (foundDot)
                {
                    tokens->AddToken(Tokens.CONST_FLOAT_TOKEN.New(number, lineCounter));
                }
                else
                {
                    tokens->AddToken(Tokens.CONST_INT_TOKEN.New(number, lineCounter));
                }

                continue;
            }

            // --- String ---
            match = CharacterGroups.STRING_DELIMITOR.Match(character, peekCharacter);

            if (match)
            {
                std::string string = "";

                if (match == 2)
                    file->ReadNext();  // Consume the second character of the string delimitor, if it's a two character
                                       // delimitor

                while (true)
                {
                    character = file->ReadNext();      // Read next
                    peekCharacter = file->PeekNext();  // Peek next

                    match = CharacterGroups.STRING_DELIMITOR.Match(character, peekCharacter);

                    if (match)
                    {
                        if (match == 2)
                            file->ReadNext();  // Consume the second character of the string delimitor, if it's a two
                                               // character delimitor
                        break;
                    }

                    string += character;
                }

                tokens->AddToken(Tokens.CONST_STRING_TOKEN.New(string, lineCounter));

                continue;
            }

            // --- Identifier ---
            if (CharacterGroups.IDENTIFIER_START_CHAR.Match(character, peekCharacter))
            {
                std::string identifierString = std::string(1, character);

                while (CharacterGroups.IDENTIFIER_CHAR.Match(file->PeekNext(), 0))
                {
                    identifierString += file->ReadNext();
                }

                // Check whether the identifier is a keyword
                if (TryAddKeyword(tokens, identifierString)) continue;

                // Check whether the identifier is a compiler instruction
                if (TryAddCompilerInstruction(tokens, identifierString)) continue;

                tokens->AddToken(Tokens.CONST_IDENTIFIER_TOKEN.New(identifierString, lineCounter));
                continue;
            }

            if (TryAddCharacterGroupToken(file, tokens, Tokens.DOT_TOKEN, character, peekCharacter)) continue;

            // --- Equal Operators ---

            if (TryAddCharacterGroupToken(file, tokens, Tokens.EQUAL_OPERATOR_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.NOT_EQUAL_OPERATOR_TOKEN, character, peekCharacter)) continue;
            // less/greater than or equal operators must be checked after less/greater than operators as otherwise they are parsed as two separate
            // tokens
            if (TryAddCharacterGroupToken(file, tokens, Tokens.GREATER_THAN_OR_EQUAL_OPERATOR_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.LESS_THAN_OR_EQUAL_OPERATOR_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.GREATER_THAN_OPERATOR_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.LESS_THAN_OPERATOR_TOKEN, character, peekCharacter)) continue;

            // --- Assign Operators ---
            if (TryAddCharacterGroupToken(file, tokens, Tokens.ASSIGN_OPERATOR_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.ADD_ASSIGN_OPERATOR_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.SUB_ASSIGN_OPERATOR_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.MUL_ASSIGN_OPERATOR_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.DIV_ASSIGN_OPERATOR_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.MOD_ASSIGN_OPERATOR_TOKEN, character, peekCharacter)) continue;

            // --- Increment and Decrement Operators ---
            if (TryAddCharacterGroupToken(file, tokens, Tokens.INCREMENT_OPERATOR_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.DECREMENT_OPERATOR_TOKEN, character, peekCharacter)) continue;

            // --- Arithmetic Operators ---
            if (TryAddCharacterGroupToken(file, tokens, Tokens.ADD_OPERATOR_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.SUB_OPERATOR_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.MUL_OPERATOR_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.DIV_OPERATOR_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.MOD_OPERATOR_TOKEN, character, peekCharacter)) continue;

            // --- Negate Operator ---
            // TODO: Issue here as this will be parsed as a sub operator
            if (TryAddCharacterGroupToken(file, tokens, Tokens.NEGATE_OPERATOR_TOKEN, character, peekCharacter)) continue;

            // --- Logical Operators ---
            if (TryAddCharacterGroupToken(file, tokens, Tokens.AND_OPERATOR_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.OR_OPERATOR_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.NOT_OPERATOR_TOKEN, character, peekCharacter)) continue;

            // --- Unknown Token ---
            std::cout << "Unknown token: " << character << "\n";
        }

        return tokens;
    }
} Scanner;
#pragma once

#include <iostream>

#include "../InputFile.cpp"
#include "../tokens/CharacterGroupToken.cpp"
#include "../tokens/CompilerInstructions.cpp"
#include "../tokens/Keywords.cpp"
#include "../tokens/TokenList.cpp"
#include "../tokens/TokenWithValue.cpp"
#include "../tokens/Tokens.cpp"
#include "../tokens/characterGroups/CharacterGroups.cpp"

static class Scanner
{
   public:
    TokenList* Scan(InputFile* file);

   private:
    bool TryAddCharacterGroupToken(InputFile* file, TokenList* tokens, std::shared_ptr<CharacterGroupToken> token, char consumedCharacter,
                                   char peekCharacter);

} Scanner;

bool Scanner::TryAddCharacterGroupToken(InputFile* file, TokenList* tokens, std::shared_ptr<CharacterGroupToken> token, char consumedCharacter,
                                        char peekCharacter)
{
    unsigned int match = token->Match(consumedCharacter, peekCharacter);

    if (match == 0) return false;

    tokens->AddToken(token);

    if (match == 2) file->ReadNext();  // As the peek character matched aswell we need to consume it

    return true;
}

TokenList* Scanner::Scan(InputFile* file)
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

        // Ignore whitespaces
        if (CharacterGroups.WHITESPACES.Match(character, peekCharacter))
        {
            continue;
        }

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
                tokens->AddToken(std::shared_ptr<TokenWithValue>(Tokens.CONST_FLOAT_TOKEN->Clone(number)));
            }
            else
            {
                tokens->AddToken(std::shared_ptr<TokenWithValue>(Tokens.CONST_INT_TOKEN->Clone(number)));
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

            tokens->AddToken(std::shared_ptr<TokenWithValue>(Tokens.CONST_STRING_TOKEN->Clone(string)));

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
            std::shared_ptr<AbstractKeywordToken> keywordToken = Keywords.GetKeywordToken(identifierString);

            if (keywordToken != nullptr)
            {
                tokens->AddToken(keywordToken);
                continue;
            }

            // Check whether the identifier is a compiler instruction
            std::shared_ptr<AbstractCompilerInstructionToken> compilerInstructionToken =
                CompilerInstructions.GetCompilerInstructionToken(identifierString);

            if (compilerInstructionToken != nullptr)
            {
                tokens->AddToken(compilerInstructionToken);
                continue;
            }

            tokens->AddToken(std::shared_ptr<TokenWithValue>(Tokens.CONST_IDENTIFIER_TOKEN->Clone(identifierString)));
            continue;
        }

        if (TryAddCharacterGroupToken(file, tokens, Tokens.DOT_TOKEN, character, peekCharacter)) continue;

        // --- Equal Operators ---

        if (TryAddCharacterGroupToken(file, tokens, Tokens.EQUAL_OPERATOR_TOKEN, character, peekCharacter)) continue;
        if (TryAddCharacterGroupToken(file, tokens, Tokens.NOT_EQUAL_OPERATOR_TOKEN, character, peekCharacter)) continue;
        // less/greater than or equal operators must be checked after less/greater than operators as otherwise they are parsed as two separate tokens
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
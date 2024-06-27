#pragma once

#include <iostream>

#include "../InputFile.cpp"
#include "../tokens/CharacterGroupToken.cpp"
#include "../tokens/ConstTokens.cpp"
#include "../tokens/TokenList.cpp"
#include "../tokens/characterGroups/CharacterGroups.cpp"
#include "../tokens/notConstTokens/IdentifierToken.cpp"
#include "../tokens/notConstTokens/NumberConstToken.cpp"
#include "../tokens/notConstTokens/StringConstToken.cpp"

static class Scanner
{
   public:
    TokenList* Scan(InputFile* file);

   private:
    bool TryAddCharacterGroupToken(InputFile* file, TokenList* tokens, std::shared_ptr<CharacterGroupToken> token,
                                   char consumedCharacter, char peekCharacter);

} Scanner;

bool Scanner::TryAddCharacterGroupToken(InputFile* file, TokenList* tokens, std::shared_ptr<CharacterGroupToken> token,
                                        char consumedCharacter, char peekCharacter)
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

        if (TryAddCharacterGroupToken(file, tokens, ConstTokens.PARENTHESIS_OPEN_TOKEN, character, peekCharacter))
            continue;
        if (TryAddCharacterGroupToken(file, tokens, ConstTokens.PARENTHESIS_CLOSE_TOKEN, character, peekCharacter))
            continue;

        if (TryAddCharacterGroupToken(file, tokens, ConstTokens.BRACES_OPEN_TOKEN, character, peekCharacter)) continue;
        if (TryAddCharacterGroupToken(file, tokens, ConstTokens.BRACES_CLOSE_TOKEN, character, peekCharacter)) continue;

        if (TryAddCharacterGroupToken(file, tokens, ConstTokens.SEPARATOR_TOKEN, character, peekCharacter)) continue;

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

            while (CharacterGroups.NUMBERS.Match(
                file->PeekNext(), 0))  // INFO: It's a bit of a hack to pass 0 as the second argument; but should work
            {
                number += file->ReadNext();
            }

            tokens->AddToken(std::shared_ptr<NumberConstToken>(new NumberConstToken(number)));

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

            tokens->AddToken(std::shared_ptr<StringConstToken>(new StringConstToken(string)));

            continue;
        }

        // --- Identifier ---
        if (CharacterGroups.IDENTIFIER.Match(character, peekCharacter))
        {
            std::string identifierString = std::string(1, character);

            while (CharacterGroups.IDENTIFIER.Match(file->PeekNext(), 0))
            {
                identifierString += file->ReadNext();
            }

            tokens->AddToken(std::shared_ptr<IdentifierToken>(new IdentifierToken(identifierString)));

            continue;
        }

        // --- Unknown Token ---
        std::cout << "Unknown token: " << character << "\n";
    }

    return tokens;
}
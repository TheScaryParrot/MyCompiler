#pragma once

#include "../tokens/TokenList.cpp"
#include "../InputFile.cpp"
#include "characterGroups/CharacterGroups.cpp"
#include "characterGroups/Keywords.cpp"

static class Scanner {
public:
    TokenList Scan(InputFile* file);

private:

}Scanner;

TokenList Scanner::Scan(InputFile* file) {
    TokenList tokens = TokenList();

    if (!file->IsGood()) {
        return tokens;
    }

    while (!file->IsEndOfFile()) {
        std::string character = file->ReadNext();
        
        // Ignore whitespaces
        if (CharacterGroups.WHITESPACES.Contains(character)) {continue;}

        // Statement end
        if (CharacterGroups.STATEMENT_END.Contains(character)) {
            // TODO: Add statement end token to tokens
            continue;
        }

        if (CharacterGroups.BODY_OPEN.Contains(character)) {
            // TODO: Add body open token to tokens
            continue;
        }

        if (CharacterGroups.BODY_CLOSE.Contains(character)) {
            // TODO: Add body close token to tokens
            continue;
        }

        if (CharacterGroups.PARENTHESIS_OPEN.Contains(character)) {
            //TODO: Add parenthesis open token to tokens
            continue;
        }

        if (CharacterGroups.PARENTHESIS_CLOSE.Contains(character)) {
            //TODO: Add parenthesis close token to tokens
            continue;
        }

        // Single-line comment
        if (character == "/") {
            if (file->PeekNext() == "/") {
                while (file->PeekNext() != "\n") {
                    file->ReadNext();
                }
            }

            continue;
        }

        // Multi-line comment
        if (character == "\\\\") {
            std::string string = character;
            while (file->PeekNext() != "\\\\") {
                string += file->ReadNext();
            }

            continue;
        }

        // Number
        if (CharacterGroups.NUMBERS.Contains(character)) {
            std::string number = character;
            while (CharacterGroups.NUMBERS.Contains(file->PeekNext())) {
                number += file->ReadNext();
            }

            // TODO: Add number token to tokens

            continue;
        }
        
        // String
        if (character == "\"") {
            std::string string = "";
            std::string next = "";

            unsigned int i = 0;

            while (i < 10000) {
                next = file->ReadNext();
                if (next == "\"") {break;}
                string += next;
                i++;
            }

            // TODO: Add string token to tokens

            continue;
        }

        // Identifier
        if (CharacterGroups.ALPHABET.Contains(character)) {
            std::string identifier = character;
            while (CharacterGroups.ALPHANUMERIC.Contains(file->PeekNext())) {
                identifier += file->ReadNext();
            }

            AbstractToken* token = Keywords.GetKeywordToken(identifier);

            if (token != nullptr)
            {
                tokens.AddToken(token);
            }
            else 
            {
                //TODO: Add identifier token to tokens
            }

            continue;
        }
    }

    return tokens;
}
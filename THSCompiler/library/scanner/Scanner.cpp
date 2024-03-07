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
        std::string next = file->ReadNext();

        // Ignore whitespaces
        if (CharacterGroups.WHITESPACES.Contains(next)) {continue;}

        // Statement end
        if (CharacterGroups.STATEMENT_END.Contains(next)) {
            // TODO: Add statement end token to tokens
            continue;
        }

        if (CharacterGroups.BODY_OPEN.Contains(next)) {
            // TODO: Add body open token to tokens
            continue;
        }

        if (CharacterGroups.BODY_CLOSE.Contains(next)) {
            // TODO: Add body close token to tokens
            continue;
        }

        if (CharacterGroups.PARENTHESIS_OPEN.Contains(next)) {
            //TODO: Add parenthesis open token to tokens
            continue;
        }

        if (CharacterGroups.PARENTHESIS_CLOSE.Contains(next)) {
            //TODO: Add parenthesis close token to tokens
            continue;
        }

        // Single-line comment
        if (next == "/") {
            if (file->PeekNext() == "/") {
                while (file->PeekNext() != "\n") {
                    file->ReadNext();
                }
            }

            continue;
        }

        // Multi-line comment
        if (next == "\\\\") {
            std::string string = next;
            while (file->PeekNext() != "\\\\") {
                string += file->ReadNext();
            }

            continue;
        }

        // Number
        if (CharacterGroups.NUMBERS.Contains(next)) {
            std::string number = next;
            while (CharacterGroups.NUMBERS.Contains(file->PeekNext())) {
                number += file->ReadNext();
            }

            // TODO: Add number token to tokens

            continue;
        }

        // String
        if (next == "\"") {
            std::string string = "";
            while (file->ReadNext() != "\"") {
                string += file->ReadNext();
            }

            // TODO: Add string token to tokens

            continue;
        }

        // Identifier
        if (CharacterGroups.ALPHABET.Contains(next)) {
            std::string identifier = next;
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
#pragma once

#include <iostream>

#include "../InputFile.cpp"

#include "../InputFile.cpp"

#include "../tokens/TokenList.cpp"

#include "../tokens/ConstTokens.cpp"
#include "../tokens/Keywords.cpp"
#include "../tokens/notConstTokens/IdentifierToken.cpp"
#include "../tokens/notConstTokens/StringConstToken.cpp"
#include "../tokens/notConstTokens/NumberConstToken.cpp"

#include "../tokens/characterGroups/CharacterGroups.cpp"


static class Scanner {
public:
    TokenList* Scan(InputFile* file);

}Scanner;

TokenList* Scanner::Scan(InputFile* file) {
    TokenList* tokens = new TokenList();

    if (!file->IsGood()) {
        throw "Can't scan InputFile. file is not good";
    }

    while (!file->IsEndOfFile()) {
        std::string character = file->ReadNext();
        
        // Ignore whitespaces
        if (CharacterGroups.WHITESPACES.Contains(character)) {continue;}

        // --- Delimitors ---
        if (ConstTokens.STATEMENT_END_TOKEN.IsInCharacterGroup(character)) {
            tokens->AddToken(&ConstTokens.STATEMENT_END_TOKEN);
            continue;
        }

        if (ConstTokens.BODY_OPEN_TOKEN.IsInCharacterGroup(character)) {
            tokens->AddToken(&ConstTokens.BODY_OPEN_TOKEN);
            continue;
        }

        if (ConstTokens.BODY_CLOSE_TOKEN.IsInCharacterGroup(character)) {
            tokens->AddToken(&ConstTokens.BODY_CLOSE_TOKEN);
            continue;
        }
        
        if (ConstTokens.PARENTHESIS_OPEN_TOKEN.IsInCharacterGroup(character)) {
            tokens->AddToken(&ConstTokens.PARENTHESIS_OPEN_TOKEN);
            continue;
        }

        if (ConstTokens.PARENTHESIS_CLOSE_TOKEN.IsInCharacterGroup(character)) {
            tokens->AddToken(&ConstTokens.PARENTHESIS_CLOSE_TOKEN);
            continue;
        }

        if (ConstTokens.SEPERATOR_TOKEN.IsInCharacterGroup(character)) {
            tokens->AddToken(&ConstTokens.SEPERATOR_TOKEN);
            continue;
        }

        // --- Single-line comment ---
        if (character == "/") {
            if (file->PeekNext() == "/") {
                while (file->PeekNext() != "\n") {
                    file->ReadNext();
                }
            }

            continue;
        }

        // --- Multi-line comment ---
        if (character == "\\") {
            if (file->PeekNext() == "\\") {
                while (true) {
                    if (file->PeekNext() == "\\") {
                        if (file->PeekNext() == "\\") {
                            break;
                        }
                    }

                    file->ReadNext();
                }
            }

            continue;
        }

        // --- Number ---
        if (CharacterGroups.NUMBERS.Contains(character)) {
            std::string number = character;
            while (CharacterGroups.NUMBERS.Contains(file->PeekNext())) {
                number += file->ReadNext();
            }

            tokens->AddToken(new NumberConstToken(number));

            continue;
        }
        
        // --- String ---
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

            tokens->AddToken(new StringConstToken(string));

            continue;
        }

        // --- Identifier ---
        if (CharacterGroups.IDENTIFIER_START_CHAR.Contains(character)) {
            std::string identifierString = character;
            while (CharacterGroups.IDENTIFIER_CHAR.Contains(file->PeekNext())) {
                identifierString += file->ReadNext();
            }

            // Check whether the identifier is a keyword
            AbstractKeywordToken* keywordToken = Keywords.GetKeywordToken(identifierString);

            if (keywordToken != nullptr)
            {
                tokens->AddToken(keywordToken);
            }
            else 
            {
                tokens->AddToken(new IdentifierToken(identifierString));
            }

            continue;
        }

        // --- Arithmetic Operators ---
        if (ConstTokens.ADD_OPERATOR_TOKEN.IsInCharacterGroup(character)) {
            tokens->AddToken(&ConstTokens.ADD_OPERATOR_TOKEN);
            continue;
        }

        if (ConstTokens.SUB_OPERATOR_TOKEN.IsInCharacterGroup(character)) {
            tokens->AddToken(&ConstTokens.SUB_OPERATOR_TOKEN);
            continue;
        }

        if (ConstTokens.MUL_OPERATOR_TOKEN.IsInCharacterGroup(character)) {
            tokens->AddToken(&ConstTokens.MUL_OPERATOR_TOKEN);
            continue;
        }

        if (ConstTokens.DIV_OPERATOR_TOKEN.IsInCharacterGroup(character)) {
            tokens->AddToken(&ConstTokens.DIV_OPERATOR_TOKEN);
            continue;
        }

        if (ConstTokens.MOD_OPERATOR_TOKEN.IsInCharacterGroup(character)) {
            tokens->AddToken(&ConstTokens.MOD_OPERATOR_TOKEN);
            continue;
        }

        // --- Equal Operators ---
        if (ConstTokens.EQUAL_OPERATOR_TOKEN.IsInCharacterGroup(character)) {
            tokens->AddToken(&ConstTokens.EQUAL_OPERATOR_TOKEN);
            continue;
        }

        if (ConstTokens.NOT_EQUAL_OPERATOR_TOKEN.IsInCharacterGroup(character)) {
            tokens->AddToken(&ConstTokens.NOT_EQUAL_OPERATOR_TOKEN);
            continue;
        }

        if (ConstTokens.GREATER_THAN_OPERATOR_TOKEN.IsInCharacterGroup(character)) {
            tokens->AddToken(&ConstTokens.GREATER_THAN_OPERATOR_TOKEN);
            continue;
        }

        if (ConstTokens.LESS_THAN_OPERATOR_TOKEN.IsInCharacterGroup(character)) {
            tokens->AddToken(&ConstTokens.LESS_THAN_OPERATOR_TOKEN);
            continue;
        }

        if (ConstTokens.GREATER_THAN_OR_EQUAL_OPERATOR_TOKEN.IsInCharacterGroup(character)) {
            tokens->AddToken(&ConstTokens.GREATER_THAN_OR_EQUAL_OPERATOR_TOKEN);
            continue;
        }

        if (ConstTokens.LESS_THAN_OR_EQUAL_OPERATOR_TOKEN.IsInCharacterGroup(character)) {
            tokens->AddToken(&ConstTokens.LESS_THAN_OR_EQUAL_OPERATOR_TOKEN);
            continue;
        }

        // --- Assign Operators ---
        if (ConstTokens.ASSIGN_OPERATOR_TOKEN.IsInCharacterGroup(character)) {
            tokens->AddToken(&ConstTokens.ASSIGN_OPERATOR_TOKEN);
            continue;
        }

        if (ConstTokens.ADD_ASSIGN_OPERATOR_TOKEN.IsInCharacterGroup(character)) {
            tokens->AddToken(&ConstTokens.ADD_ASSIGN_OPERATOR_TOKEN);
            continue;
        }

        if (ConstTokens.SUB_ASSIGN_OPERATOR_TOKEN.IsInCharacterGroup(character)) {
            tokens->AddToken(&ConstTokens.SUB_ASSIGN_OPERATOR_TOKEN);
            continue;
        }

        if (ConstTokens.MUL_ASSIGN_OPERATOR_TOKEN.IsInCharacterGroup(character)) {
            tokens->AddToken(&ConstTokens.MUL_ASSIGN_OPERATOR_TOKEN);
            continue;
        }

        if (ConstTokens.DIV_ASSIGN_OPERATOR_TOKEN.IsInCharacterGroup(character)) {
            tokens->AddToken(&ConstTokens.DIV_ASSIGN_OPERATOR_TOKEN);
            continue;
        }

        if (ConstTokens.MOD_ASSIGN_OPERATOR_TOKEN.IsInCharacterGroup(character)) {
            tokens->AddToken(&ConstTokens.MOD_ASSIGN_OPERATOR_TOKEN);
            continue;
        }

        // --- Increment and Decrement Operators ---
        if (ConstTokens.INCREMENT_OPERATOR_TOKEN.IsInCharacterGroup(character)) {
            tokens->AddToken(&ConstTokens.INCREMENT_OPERATOR_TOKEN);
            continue;
        }

        if (ConstTokens.DECREMENT_OPERATOR_TOKEN.IsInCharacterGroup(character)) {
            tokens->AddToken(&ConstTokens.DECREMENT_OPERATOR_TOKEN);
            continue;
        }

        // --- Negate Operator ---
        if (ConstTokens.NEGATE_OPERATOR_TOKEN.IsInCharacterGroup(character)) {
            tokens->AddToken(&ConstTokens.NEGATE_OPERATOR_TOKEN);
            continue;
        }

        // --- Logical Operators ---
        if (ConstTokens.AND_OPERATOR_TOKEN.IsInCharacterGroup(character)) {
            tokens->AddToken(&ConstTokens.AND_OPERATOR_TOKEN);
            continue;
        }

        if (ConstTokens.OR_OPERATOR_TOKEN.IsInCharacterGroup(character)) {
            tokens->AddToken(&ConstTokens.OR_OPERATOR_TOKEN);
            continue;
        }

        if (ConstTokens.NOT_OPERATOR_TOKEN.IsInCharacterGroup(character)) {
            tokens->AddToken(&ConstTokens.NOT_OPERATOR_TOKEN);
            continue;
        }


        // --- Unknown Token ---
        std::cout << "Unknown token: " + character + "\n";
    }

    return tokens;
}
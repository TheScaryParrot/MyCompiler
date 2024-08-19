#pragma once

#include <iostream>
#include <queue>
#include <vector>

#include "../../InputFile.cpp"
#include "../../Order.cpp"
#include "IOrderFetcher.cpp"

class CharacterGroup
{
   public:
    CharacterGroup(size_t length, char* characters)
    {
        for (size_t i = 0; i < length; i++)
        {
            this->characters.push_back(characters[i]);
        }

        delete[] characters;
    }

    bool IsCharacterInGroup(char character)
    {
        for (char c : characters)
        {
            if (c == character)
            {
                return true;
            }
        }

        return false;
    }

   private:
    std::vector<char> characters;
};

class InputFileFetcher : public IOrderFetcher
{
   public:
    InputFileFetcher(InputFile* file)
    {
        if (file == nullptr)
        {
            std::cerr << "Error: file is null" << std::endl;
        }

        this->file = file;
    }

    virtual Order Next() override
    {
        if (!file->IsGood())
        {
            std::cerr << "Error: file is not good" << std::endl;
            return Order::Empty();
        }

        ClearWhitespaces(file);

        char character = file->PeekNext();
        Order::EOrderTypes type = Order::Identifier;
        std::string name = "";

        if (directCode.IsCharacterInGroup(character))
        {
            file->ReadNext();
            character = file->PeekNext();
            type = Order::DirectCode;

            while (!file->IsEndOfFile() && !directCode.IsCharacterInGroup(character))
            {
                file->ReadNext();
                name += character;
                character = file->PeekNext();
            }

            file->ReadNext();
            return Order(name, type);
        }

        if (compilerInstruction.IsCharacterInGroup(character))
        {
            file->ReadNext();
            character = file->PeekNext();
            type = Order::CompilerInstruction;
        }

        while (!file->IsEndOfFile() && !whitespace.IsCharacterInGroup(character) &&
               !compilerInstruction.IsCharacterInGroup(character) && !directCode.IsCharacterInGroup(character))
        {
            file->ReadNext();
            name += character;
            character = file->PeekNext();
        }

        ClearWhitespaces(file);

        return Order(name, type);
    }

    virtual bool IsEmpty() override { return file->IsEndOfFile(); }

   private:
    void ClearWhitespaces(InputFile* file)
    {
        while (!file->IsEndOfFile() && whitespace.IsCharacterInGroup(file->PeekNext()))
        {
            file->ReadNext();
        }
    }

    InputFile* file;

    CharacterGroup whitespace = CharacterGroup(4, new char[4]{' ', '\n', '\t', '\r'});
    CharacterGroup compilerInstruction = CharacterGroup(1, new char[1]{'#'});
    CharacterGroup directCode = CharacterGroup(1, new char[1]{'"'});
};
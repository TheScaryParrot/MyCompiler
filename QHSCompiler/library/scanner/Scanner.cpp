#pragma once

#include <iostream>
#include <queue>
#include <vector>

#include "../InputFile.cpp"
#include "../OrderQueue.cpp"

class CharacterGroup
{
   public:
    CharacterGroup(size_t length, char* characters)
    {
        for (size_t i = 0; i < length; i++)
        {
            this->characters.push_back(characters[i]);
        }
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

class Scanner
{
   public:
    OrderQueue* ScanFile(InputFile* file);

   private:
    CharacterGroup whitespace = CharacterGroup(4, new char[4]{' ', '\n', '\t', '\r'});
    CharacterGroup compilerInstruction = CharacterGroup(1, new char[1]{'#'});
};

OrderQueue* Scanner::ScanFile(InputFile* file)
{
    if (file == nullptr)
    {
        std::cerr << "Error: file is null" << std::endl;
        return nullptr;
    }

    if (!file->IsGood())
    {
        std::cerr << "Error: file is not good" << std::endl;
        return nullptr;
    }

    OrderQueue* orders = new OrderQueue();

    char peekChar;
    Order::EOrderTypes type = Order::Identifier;
    std::string name = "";

    while (!file->IsEndOfFile())
    {
        peekChar = file->PeekNext();

        if (file->IsEndOfFile() || whitespace.IsCharacterInGroup(peekChar))
        {
            if (name != "")
            {
                orders->Push(Order(name, type));
                name = "";
            }

            type = Order::Identifier;
            file->ReadNext();
            continue;
        }

        if (compilerInstruction.IsCharacterInGroup(peekChar))
        {
            if (name != "")
            {
                orders->Push(Order(name, type));
                name = "";
            }

            type = Order::CompilerInstruction;
            file->ReadNext();

            continue;
        }

        name += file->ReadNext();
    }

    return orders;
}

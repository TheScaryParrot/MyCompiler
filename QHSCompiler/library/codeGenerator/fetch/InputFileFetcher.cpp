#pragma once

#include <iostream>
#include <queue>
#include <vector>

#include "../../InputFile.cpp"
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
    ~InputFileFetcher() { delete file; }

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
            type = Order::LiteralCode;

            while (!file->IsEndOfFile() && !directCode.IsCharacterInGroup(character))
            {
                // Increment line if linebreak inside of direct code
                if (linebreak.IsCharacterInGroup(character)) line++;

                file->ReadNext();
                name += character;
                character = file->PeekNext();
            }

            file->ReadNext();
            Order order = Order(name, type, line);
            lastOrder = order;
            return order;
        }

        if (compilerInstruction.IsCharacterInGroup(character))
        {
            file->ReadNext();
            character = file->PeekNext();
            type = Order::Instruction;
        }

        while (!file->IsEndOfFile() && !whitespace.IsCharacterInGroup(character) &&
               !compilerInstruction.IsCharacterInGroup(character) && !directCode.IsCharacterInGroup(character))
        {
            file->ReadNext();
            name += character;
            character = file->PeekNext();
        }

        ClearWhitespaces(file);

        Order order = Order(name, type, line);
        lastOrder = order;
        return order;
    }

    virtual bool IsEmpty() override { return file->IsEndOfFile(); }

    virtual std::string GetLastOrderLog() override { return lastOrder.ToLogString(); }

   private:
    void ClearWhitespaces(InputFile* file)
    {
        while (true)
        {
            if (file->IsEndOfFile()) return;

            if (linebreak.IsCharacterInGroup(file->PeekNext()))
            {
                line++;
                file->ReadNext();
                continue;
            }

            if (whitespace.IsCharacterInGroup(file->PeekNext()))
            {
                file->ReadNext();
                continue;
            }

            return;
        }
    }

    InputFile* file;

    CharacterGroup whitespace = CharacterGroup(3, new char[3]{' ', '\n', '\t'});
    CharacterGroup linebreak = CharacterGroup(1, new char[1]{'\n'});
    CharacterGroup compilerInstruction = CharacterGroup(1, new char[1]{'#'});
    CharacterGroup directCode = CharacterGroup(1, new char[1]{'"'});

    unsigned int line = 1;
    Order lastOrder = Order::Empty();
};
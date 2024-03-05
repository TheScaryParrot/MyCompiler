#pragma once

#include <fstream>
#include <iostream>

#include "CodeLine.cpp"

class InputFile {
public:
    InputFile(std::string fileName)
    {
        file.open(fileName);
    }

    ~InputFile()
    {
        file.close();
    }

    bool IsOpen()
    {
        return file.is_open();
    }

    bool IsGood()
    {
        return file.good();
    }

    std::ifstream* GetFile()
    {
        return &file;
    }

    CodeLine GetNextLine()
    {
        bool isInComment = false;

        CodeLine codeLine(currentLine);

        std::string currentString = "";

        char character;

        // Get arguments
        while (this->IsGood())
        {
            GetFile()->read(&character, 1);

            if (character == '/') // Check for comments
            {
                if (GetFile()->peek() == '/')
                {
                    GetFile()->ignore(1);
                    isInComment = !isInComment;
                    continue;
                }
            }
            else if (isInComment) {continue;}
            else if (character == '\n') {character = ' '; this->currentLine++;}
            else if (character == '\r') {character = ' '; this->currentLine++;}
            else if (character == '\t') {character = ' ';}
            else if (character == ';') 
            {
                codeLine.AddString(currentString); 
                
                if (codeLine.IsEmpty()) {continue;}
                else {break;}
            }
            else if (character == '{') 
            {
                currentString += character;
                codeLine.AddString(currentString);
                break;
            }
            else if (character == '}')
            {
                currentString += character;
                codeLine.AddString(currentString);
                break;
            }

            // If end of word is reached, add it to the code line
            if (character == ' ')
            {
                codeLine.AddString(currentString);
                currentString = "";
            }
            else
            {
                currentString += character;
            }
        }

        return codeLine;
    }

private:
    std::ifstream file;
    int currentLine = 0;
};
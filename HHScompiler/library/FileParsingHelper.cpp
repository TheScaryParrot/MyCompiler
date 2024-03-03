#pragma once

#include <string>
#include <fstream>

#include "CodeLine.cpp"

static class FileParsingHelper {
public:
    CodeLine GetNextLine(std::ifstream* file)
    {
        bool isInComment = false;

        std::string instruction;
        std::vector<std::string> arguments;

        std::string currentString;
        bool hasFoundInstruction = false;

        // Get arguments
        while (file->good())
        {
            char character;
            file->read(&character, 1);

            // Skip empty spaces
            if (currentString == "" && character == ' ') continue;

            if (character == '/') // Check for comments
            {
                if (file->peek() == '/')
                {
                    file->ignore(1);
                    isInComment = !isInComment;
                    continue;
                }
            }
            else if (isInComment) continue;
            else if (character == '\n') character = ' ';
            else if (character == '\r') character = ' ';
            else if (character == '\t') character = ' ';
            else if (character == ';') break;
            else if (character == '{') break;
            else if (character == '}') break;
            
            if (character == ' ' && !hasFoundInstruction)
            {
                instruction = currentString;
                currentString = "";
                hasFoundInstruction = true;
            }
            else if (character == ' ' && hasFoundInstruction)
            {
                arguments.push_back(currentString);
                currentString = "";
            }
            else
            {
                currentString += character;
            }
        }

        return CodeLine(instruction, arguments);
    }

    void RemovePrecedingSpaces(std::string* line)
    {   
        int i = 0;
        while (line->size() > 0 && line->at(i) == ' ')
        {
            line->erase(0, 1);
        }
    }

} FileParsingHelper;
#pragma once

#include <string>
#include <fstream>

static class FileParsingHelper {
public:
    std::string GetNextLine(std::ifstream* file)
    {
        std::string line;

        bool isInComment = false;

        while (file->good())
        {
            char character;
            file->read(&character, 1);

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
            
            

            line += character;
        }

        return line;
    }

    void RemovePrecedingSpaces(std::string* line)
    {   
        int i = 0;
        while (line->size() > 0 && line->at(i) == ' ')
        {
            line->erase(0, 1);
        }
    }

    std::string GetInstruction(std::string line)
    {
        if (line.size() <= 0) return "";

        std::string instruction;

        RemovePrecedingSpaces(&line);

        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == ' ') break;
            else instruction += line[i];
        }

        return instruction;
    }

} FileParsingHelper;
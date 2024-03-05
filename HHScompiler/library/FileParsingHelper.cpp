#pragma once

#include <string>
#include <fstream>

#include "CodeLine.cpp"

static class FileParsingHelper {
public:
    void RemovePrecedingSpaces(std::string* line)
    {   
        int i = 0;
        while (line->size() > 0 && line->at(i) == ' ')
        {
            line->erase(0, 1);
        }
    }

} FileParsingHelper;
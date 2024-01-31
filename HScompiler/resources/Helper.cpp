#pragma once

#include <sstream>
#include <vector>

std::vector<std::string> SplitString(std::string str, char delimiter)
{
    std::vector<std::string> result;
    std::istringstream iss(str);
    std::string token;

    while (std::getline(iss, token, delimiter))
    {
        // Ignore empty tokens (can occure when there are multiple delimiters in a row)
        if (token == "")
        {
            continue;
        }

        result.push_back(token);
    }

    return result;
}

std::string RemoveComment(std::string line)
{
    std::vector<std::string> lineParts = SplitString(line, ';');

    if (lineParts.size() <= 0)
    {
        return "";
    }

    // Return the first element (the instruction)
    return lineParts[0];
}

std::string GetComment(std::string line)
{
    std::vector<std::string> lineParts = SplitString(line, ';');

    if (lineParts.size() <= 1)
    {
        return "";
    }

    // Return the second element (the comment) with the comment prefix
    return ";" + lineParts[1];
}

std::vector<std::string> GetArguments(std::string line)
{
    line = RemoveComment(line);
    std::vector<std::string> result = SplitString(line, ' ');

    // Remove the first element (the instruction name)
    result.erase(result.begin());

    return result;
}
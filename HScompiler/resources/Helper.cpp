#pragma once

#include <sstream>
#include <vector>

/// @brief Splits a string into a vector of strings by a delimiter
/// @param str The string to split
/// @param delimiter The delimiter to split the string by
/// @param maxParts The maximum amount of parts to split the string into (0 = no limit)
/// @return The vector of strings
std::vector<std::string> SplitString(std::string str, char delimiter, unsigned int maxParts = 0)
{
    std::vector<std::string> result;
    std::istringstream stringStream(str);
    std::string token;

    int i = 1;

    while (stringStream.good())
    {
        // If maxParts is not 0 and this part is the last part, add the rest of the string as a part
        if (maxParts != 0 && i >= maxParts)
        {
            std::getline(stringStream, token, '\0'); // Gets the rest of the string until the terminating character
            result.push_back(token);
            break;
        }

        std::getline(stringStream, token, delimiter);

        // Ignore empty tokens (can occure when there are multiple delimiters in a row)
        if (token == "")
        {
            continue;
        }

        result.push_back(token);
        i++;
    }

    return result;
}

/// @brief Removes the comment from a line
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

/// @brief Gets the comment from a line
std::string GetComment(std::string line)
{
    std::vector<std::string> lineParts = SplitString(line, ';', 2);

    if (lineParts.size() <= 1)
    {
        return "";
    }

    // Return the second element (the comment) with the comment prefix
    return ";" + lineParts[1];
}

/// @brief Gets the instruction name from a line
std::string GetInstructionName(std::string line)
{
    line = RemoveComment(line);
    std::vector<std::string> lineParts = SplitString(line, ' ');

    if (lineParts.size() <= 0)
    {
        return "";
    }

    // Return the first element (the instruction)
    return lineParts[0];
}

/// @brief Removes the instruction name from a line
std::string RemoveInstructionName(std::string line)
{
    std::vector<std::string> lineParts = SplitString(line, ' ', 2);

    if (lineParts.size() <= 1)
    {
        return "";
    }

    // Return the second element (the instruction)
    return lineParts[1];
}

/// @brief Removes leading and trailing whitespace from a string
std::string RemoveLeadingAndTrailingWhitespace(std::string str)
{
    str.erase(0, str.find_first_not_of(' '));
    str.erase(str.find_last_not_of(' ') + 1);

    return str;
}   

/// @brief Gets the arguments from a line
std::vector<std::string> GetArguments(std::string line)
{
    line = RemoveComment(line);
    line = RemoveInstructionName(line);

    std::vector<std::string> lineParts = SplitString(line, ',');
    std::vector<std::string> result;

    for (std::string part : lineParts)
    {
        // Remove leading and trailing whitespace
        RemoveLeadingAndTrailingWhitespace(part);
        result.push_back(part);
    }

    return result;
}

/// @brief Gets the preceding spaces in a string (Can be used to keep track of indentation)
std::string GetPrecedingSpaces(std::string str)
{
    std::string result = "";

    for (char c : str)
    {
        if (c != ' ')
        {
            break;
        }

        result += c;
    }

    return result;
}
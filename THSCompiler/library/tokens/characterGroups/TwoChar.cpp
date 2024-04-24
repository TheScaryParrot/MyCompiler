#pragma once

/// @brief Holds two characters. Used by characterGroups with a consumed and a peek character.
class TwoChar 
{
public:
    TwoChar(char first)
    {
        this->first = first;
        this->second = '\0';
    }

    TwoChar(char first, char second) 
    {
        this->first = first;
        this->second = second;
    }

    /// @brief How many of the given characters match the TwoChar.
    unsigned int Match(char first, char second) const
    {
        if (this->first != first) return 0;

        if (this->second == second) return 2;

        return this->second == '\0';
    }

private:
    char first;
    char second;
};
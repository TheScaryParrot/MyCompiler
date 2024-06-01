#pragma once

#include <string>

/// @brief Represents a jump label in the code
class JumpLabel
{
public:
    JumpLabel(std::string name);

    std::string GetName();

private:
    std::string name;
};

JumpLabel::JumpLabel(std::string name)
{
    this->name = name;
}

std::string JumpLabel::GetName()
{
    return name;
}
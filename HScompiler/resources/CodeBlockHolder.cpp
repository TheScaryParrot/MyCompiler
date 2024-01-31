#pragma once

#include "CodeBlockHolder.hpp"

CodeBlockHolder::CodeBlockHolder(std::size_t precedingSpacesCount)
{
    this->precedingSpaces = std::string(precedingSpacesCount, ' ');
}

CodeBlockHolder::CodeBlockHolder(std::string precedingSpaces)
{
    this->precedingSpaces = precedingSpaces;
}

void CodeBlockHolder::AddLine(std::string line)
{
    this->codeString += precedingSpaces + line + "\n";
}

std::string CodeBlockHolder::GetString()
{
    return this->codeString;
}
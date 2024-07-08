#pragma once

#include <string>

class Type
{
   public:
    Type(std::string name, bool isStatic);

    std::string name;
    bool isStatic;

    std::string ToString();
};

Type::Type(std::string name, bool isStatic)
{
    this->name = name;
    this->isStatic = isStatic;
}

std::string Type::ToString() { return name; }
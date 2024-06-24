#pragma once

#include <string>

class Type
{
   public:
    Type(std::string name);

    std::string ToString();

   private:
    std::string name;
};

Type::Type(std::string name) { this->name = name; }

std::string Type::ToString() { return name; }
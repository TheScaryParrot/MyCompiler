#pragma once

#include <vector>

#include "../environment/IEnvironment.cpp"

class Function
{
   public:
    const std::string RETURN_VARIABLE_NAME = "return";

    bool isInline;

    IEnvironment* environment;
};
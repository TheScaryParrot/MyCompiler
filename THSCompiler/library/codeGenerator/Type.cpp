#pragma once

#include "IEnvironment.cpp"

class Type
{
   public:
    IEnvironment* environment;

    Type(IEnvironment* environment) { this->environment = environment; }
};
#pragma once

#include <string>

class AbstractStatement  
{
public:
    AbstractStatement(/* args */);
    ~AbstractStatement();

    virtual std::string GetString();
};

AbstractStatement::AbstractStatement(/* args */)
{
}

AbstractStatement::~AbstractStatement()
{
}

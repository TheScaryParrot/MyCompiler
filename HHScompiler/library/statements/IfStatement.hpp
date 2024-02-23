#include "AbstractStatement.hpp"

class IfStatement : public AbstractStatement
{
public:
    IfStatement(std::string statementLine, std::ifstream* file);
    ~IfStatement();
};

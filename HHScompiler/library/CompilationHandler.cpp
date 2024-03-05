#pragma once

#include <string>

#include "CodeLine.cpp"
#include "statements/IfStatement.cpp"

AbstractStatement* CUSTOM_STATEMENTS[] = {
    new IfStatement()
};

static class CompilationHandler {
public:
    static std::string Compile(CodeLine codeLine)
    {
        for (AbstractStatement* statement : CUSTOM_STATEMENTS)
        {
            if (statement->IsMatch(codeLine.instruction))
            {
                return statement->GetCompiledString(codeLine.arguments);
            }
        }

        return codeLine.ToString();
    }

} CompilationHandler;
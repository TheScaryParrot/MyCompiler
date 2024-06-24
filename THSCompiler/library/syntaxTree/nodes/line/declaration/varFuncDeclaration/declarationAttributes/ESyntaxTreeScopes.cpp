#pragma once

#include <string>

enum ESyntaxTreeScopes
{
    PUBLIC,
    PROTECTED,
    PRIVATE
};

std::string EScopesToString(ESyntaxTreeScopes scope)
{
    switch (scope)
    {
        case PUBLIC:
            return "public";
        case PROTECTED:
            return "protected";
        case PRIVATE:
            return "private";
    }

    throw "Couldn't convert ESyntaxTreeScopes to String. Did you forget to update EScopesToString()";
}
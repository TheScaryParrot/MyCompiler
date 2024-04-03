#pragma once

enum EScopes
{
    PUBLIC,
    PROTECTED,
    PRIVATE
};

std::string EScopesToString(EScopes scope)
{
    switch(scope)
    {
        case PUBLIC: return "public";
        case PROTECTED: return "protected";
        case PRIVATE: return "private";
    }

    return "Couldn't convert EScopes to String. Did you forget to update EScopesToString()";
}
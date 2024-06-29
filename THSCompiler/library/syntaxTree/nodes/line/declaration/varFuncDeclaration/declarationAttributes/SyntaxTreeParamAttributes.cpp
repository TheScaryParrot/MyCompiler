#pragma once

#include <string>

struct SyntaxTreeParamAttributes
{
    bool isFinal = false;
    bool isInline = false;

   public:
    std::string ToString();
};

std::string SyntaxTreeParamAttributes::ToString()
{
    std::string result = "";

    if (isFinal) result += "final ";
    if (isInline) result += "inline ";

    return result;
}
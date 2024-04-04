#pragma once

#include <string>

enum EReadWrites
{
    FULL,
    READONLY,
    CONST
};

std::string EReadWritesToString(EReadWrites readwrite)
{
    switch (readwrite)
    {
        case FULL: return "";
        case READONLY: return "readonly";
        case CONST: return "const";
    }

    throw "Couldn't convert EReadWrites to String. Did you forget to update EReadWritesToString()";
}
#pragma once

#include "../Type.cpp"

class PrimitiveType : public Type
{
   protected:
    std::string ConstructVarLocationAccess(IVariableLocation* location)
    {
        std::string result = location->ToAssemblyString();

        if (location->RequiresSizeKeyword())
        {
            result = GetSizeKeyword() + " " + result;
        }

        return result;
    }

   private:
    std::string GetSizeKeyword()
    {
        switch (this->GetSize())
        {
            case 1:
                return "byte";
            case 2:
                return "word";
            case 4:
                return "dword";
            case 8:
                return "qword";
        }

        Logger.Log("Cannot get size keyword as argument size is not 1, 2, 4 or 8", Logger::ERROR);
        return "";
    }
};
#pragma once

#include <memory>

#include "../../assembly/AssemblyCode.cpp"
#include "../../assembly/AssemblyCodeGenerator.cpp"
#include "../varLocation/IVariableLocation.cpp"

class Type
{
   public:
    virtual void GenerateAssign(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) = 0;
    virtual void GenerateAdd(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) = 0;
    virtual void GenerateSub(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) = 0;
    virtual void GenerateMul(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) = 0;
    virtual void GenerateDiv(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) = 0;
    virtual void GenerateMod(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) = 0;

    virtual void GenerateAnd(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) = 0;
    virtual void GenerateOr(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) = 0;

    virtual void GenerateEqual(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) = 0;
    virtual void GenerateNotEqual(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) = 0;
    virtual void GenerateLess(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) = 0;
    virtual void GenerateLessEqual(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) = 0;
    virtual void GenerateGreater(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) = 0;
    virtual void GenerateGreaterEqual(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) = 0;

    virtual void GenerateNot(IVariableLocation* destination, AssemblyCode* assemblyCode) = 0;
    virtual void GenerateNeg(IVariableLocation* destination, AssemblyCode* assemblyCode) = 0;
    virtual void GenerateInc(IVariableLocation* destination, AssemblyCode* assemblyCode) = 0;
    virtual void GenerateDec(IVariableLocation* destination, AssemblyCode* assemblyCode) = 0;

    virtual void GenerateStackPush(IVariableLocation* source, AssemblyCode* assemblyCode) = 0;

    /// @brief Returns the string used in assembly to define this type (eg. db for byte)
    std::string GetAssemblyDefineString()
    {
        switch (this->GetSize())
        {
            case 1:
                return "db";
            case 2:
                return "dw";
            case 4:
                return "dd";
            case 8:
                return "dq";
        }

        Logger.Log("Cannot get assembly define string as size is not 1, 2, 4 or 8", Logger::ERROR);
        return "";
    }

    /// @brief Returns whether the other type can be applied (assign, add, sum) to this one
    /// @param type other type
    virtual bool CanApplyToThis(Type* other) { return this == other; }

    virtual unsigned int GetSize() = 0;

    IVariableLocation* ShortSafeIVarlocationOfThisTypeInRegister(IVariableLocation* location, AssemblyCode* assemblyCode)
    {
        IVariableLocation* registerVarLocation = AssemblyCodeGenerator.GetNewRegistryVarLocation(this->GetSize(), assemblyCode);
        this->GenerateAssign(registerVarLocation, location, assemblyCode);
        return registerVarLocation;
    }
};
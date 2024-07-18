#pragma once

#include "../../assembly/AssemblyCode.cpp"
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

    virtual void GenerateNot(IVariableLocation* destination, AssemblyCode* assemblyCode) = 0;
    virtual void GenerateNeg(IVariableLocation* destination, AssemblyCode* assemblyCode) = 0;
    virtual void GenerateInc(IVariableLocation* destination, AssemblyCode* assemblyCode) = 0;
    virtual void GenerateDec(IVariableLocation* destination, AssemblyCode* assemblyCode) = 0;

    /// @brief Returns the string used in assembly to define this type (eg. db for byte)
    virtual std::string GetAssemblyDefineString() = 0;

    /// @brief Returns whether the other type can be applied (assign, add, sum) to this one
    /// @param type other type
    virtual bool CanApplyToThis(Type* other) { return this == other; }

    virtual unsigned int GetSize() = 0;
};
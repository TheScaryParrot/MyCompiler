#pragma once

#include <memory>

#include "../../assembly/AssemblyCode.cpp"
#include "../../assembly/AssemblyCodeGenerator.cpp"
#include "../varLocation/IVariableLocation.cpp"

class Type
{
   public:
    virtual void GenerateAssign(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                                AssemblyCode* assemblyCode) = 0;
    virtual void GenerateAdd(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) = 0;
    virtual void GenerateSub(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) = 0;
    virtual void GenerateMul(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) = 0;
    virtual void GenerateDiv(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) = 0;
    virtual void GenerateMod(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) = 0;

    virtual void GenerateAnd(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) = 0;
    virtual void GenerateOr(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                            AssemblyCode* assemblyCode) = 0;

    virtual void GenerateEqual(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                               AssemblyCode* assemblyCode) = 0;
    virtual void GenerateNotEqual(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                                  AssemblyCode* assemblyCode) = 0;
    virtual void GenerateLess(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                              AssemblyCode* assemblyCode) = 0;
    virtual void GenerateLessEqual(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                                   AssemblyCode* assemblyCode) = 0;
    virtual void GenerateGreater(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                                 AssemblyCode* assemblyCode) = 0;
    virtual void GenerateGreaterEqual(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                                      AssemblyCode* assemblyCode) = 0;

    virtual void GenerateNot(std::shared_ptr<IVariableLocation> destination, AssemblyCode* assemblyCode) = 0;
    virtual void GenerateNeg(std::shared_ptr<IVariableLocation> destination, AssemblyCode* assemblyCode) = 0;
    virtual void GenerateInc(std::shared_ptr<IVariableLocation> destination, AssemblyCode* assemblyCode) = 0;
    virtual void GenerateDec(std::shared_ptr<IVariableLocation> destination, AssemblyCode* assemblyCode) = 0;

    virtual void GenerateStackPush(std::shared_ptr<IVariableLocation> source, AssemblyCode* assemblyCode) = 0;

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

    std::shared_ptr<IVariableLocation> ShortSafeIVarlocationOfThisTypeInRegister(std::shared_ptr<IVariableLocation> location,
                                                                                 AssemblyCode* assemblyCode)
    {
        // Uses DX register (as AX might be used for operations)
        std::shared_ptr<IVariableLocation> registerVarLocation =
            std::shared_ptr<IVariableLocation>(AssemblyCodeGenerator.GetNewDXRegisterVarLocation(this->GetSize(), assemblyCode));
        this->GenerateAssign(registerVarLocation, location, assemblyCode);
        return registerVarLocation;
    }
};
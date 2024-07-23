#pragma once

#include "../../utils/Logger.cpp"
#include "IVariableLocation.cpp"

class RegistryVarLocation : public IVariableLocation
{
   private:
    std::string registry;

   public:
    RegistryVarLocation(std::string registry) { this->registry = registry; }

    virtual bool IsInline() { return false; }

    virtual IVariableLocation* Clone() { return new RegistryVarLocation(registry); }

    virtual std::string ToAssemblyString() { return registry; }
    /// @brief Retuns the string used to define the variable in the assembly code
    virtual std::string ToAssemblyDefineString()
    {
        Logger.Log("Cannot define RegistryVarLocation in assembly code", Logger::ERROR);
        return "";
    }

    /// @brief Whether a register is required as intermediate storage for the variable when trying to do operations on it (eg. memory dereference)
    virtual bool RequiresRegister() { return false; }
};
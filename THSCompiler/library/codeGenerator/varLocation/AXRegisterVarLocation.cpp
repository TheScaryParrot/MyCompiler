#pragma once

#include "../../utils/Logger.cpp"
#include "IVariableLocation.cpp"

class AXRegisterVarLocation : public IVariableLocation
{
   private:
    std::string registry;

   public:
    AXRegisterVarLocation(std::string registry) { this->registry = registry; }

    virtual bool IsInline() override { return false; }

    virtual IVariableLocation* Clone() override { return new AXRegisterVarLocation(registry); }

    virtual std::string ToAssemblyString() override { return registry; }
    /// @brief Retuns the string used to define the variable in the assembly code
    virtual std::string ToAssemblyDefineString() override
    {
        Logger.Log("Cannot define AXRegisterVarLocation in assembly code", Logger::ERROR);
        return "";
    }

    virtual bool RequiresRegister() override { return false; }
    virtual bool RequiresSizeKeyword() override { return false; }
    virtual bool IsAXregister() override { return true; }
};
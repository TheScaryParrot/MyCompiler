#pragma once

#include <iostream>

#include "IVariableLocation.cpp"

class NumConstVarLocation : public IVariableLocation
{
   private:
    std::string number;
    Type* type;

   public:
    NumConstVarLocation(std::string number, Type* type)
    {
        this->number = number;
        this->type = type;
    }

    virtual std::string GetBase() override { return number; };
    virtual void SetBase(std::string base) override { number = base; };

    virtual int GetOffset() override
    {
        std::cerr << "GetOffset() called on NumConstVarLocation. NumConstVarLocation does not support offset. Use base instead\n";
    };
    virtual void SetOffset(int offset) override
    {
        std::cerr << "SetOffset() called on NumConstVarLocation. NumConstVarLocation does not support offset. Use base instead\n";
    };
    virtual void IncrementOffset(int increment) override
    {
        std::cerr << "IncrementOffset() called on NumConstVarLocation. NumConstVarLocation does not support offset. Use base instead\n";
    };

    virtual Type* GetType() override { return type; };
    virtual void SetType(Type* type) override { this->type = type; };

    virtual IVariableLocation* Copy() override { return new NumConstVarLocation(number, type); };
    virtual IVariableLocation* ConstructionFromRelAccessBase(IVariableLocation* base) override { return this; };
};
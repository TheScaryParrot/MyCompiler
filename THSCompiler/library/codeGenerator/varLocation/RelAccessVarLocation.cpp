#pragma once

#include <iostream>

#include "IVariableLocation.cpp"

class RelAccessVarLocation : public IVariableLocation
{
   private:
    int offset;
    Type* type;

   public:
    RelAccessVarLocation(int offset, Type* type)
    {
        this->offset = offset;
        this->type = type;
    }

    virtual std::string GetBase() override
    {
        std::cerr << "GetBase() called on RelAccessVarLocation. RelAccessVarLocation does not support base as it describes a offset relative to "
                     "whatever VarLocation the base is at\n";
    };
    virtual void SetBase(std::string base) override
    {
        std::cerr << "SetBase() called on RelAccessVarLocation. RelAccessVarLocation does not support base as it describes a offset relative to "
                     "whatever VarLocation the base is at\n";
    };

    virtual int GetOffset() override { return offset; }
    virtual void SetOffset(int offset) override { this->offset = offset; }
    virtual void IncrementOffset(int increment) override { offset += increment; }

    virtual Type* GetType() override { return type; }
    virtual void SetType(Type* type) override { this->type = type; }

    virtual IVariableLocation* Copy() override { return new RelAccessVarLocation(offset, type); }
    virtual IVariableLocation* ConstructionFromRelAccessBase(IVariableLocation* base) override
    {
        IVariableLocation* copy = base->Copy();
        copy->IncrementOffset(offset);
        copy->SetType(type);
        return copy;
    }
};
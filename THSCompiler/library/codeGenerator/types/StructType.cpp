#pragma once

#include <string>

#include "../../utils/Logger.cpp"
#include "../../utils/Map.cpp"
#include "../Variable.cpp"
#include "Type.cpp"

class Property
{
   public:
    Type* type;
    unsigned int offset;

    Property(Type* type, unsigned int offset)
    {
        this->type = type;
        this->offset = offset;
    }
    Property() = default;

    Variable* Apply(IVariableLocation* location)
    {
        IVariableLocation* newLocation = location->Clone();
        newLocation->IncrementOffset(-offset);

        return new Variable(newLocation, type, false, false);
    }
};

class StructType : public Type
{
   private:
    unsigned int size;
    Map<std::string, Property> properties;

   public:
    StructType() { size = 0; }

    Property AddProperty(std::string name, Type* type)
    {
        Property property = Property(type, size);
        properties.Insert(name, property);
        size += type->GetSize();
        return property;
    }

    Property GetProperty(size_t index) { return properties.At(index).second; }

    Variable* ApplyProperty(std::string name, IVariableLocation* location)
    {
        Property property = properties.Get(name);
        return property.Apply(location);
    }

    virtual void GenerateAssign(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) override
    {
        for (size_t i = 0; i < properties.Size(); i++)
        {
            std::string propertyName = properties.At(i).first;

            Variable* destinationProperty = ApplyProperty(propertyName, destination);
            Variable* sourceProperty = ApplyProperty(propertyName, source);

            destinationProperty->type->GenerateAssign(destinationProperty->location, sourceProperty->location, assemblyCode);
        }
    }

    virtual void GenerateAdd(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot add two structs", Logger::ERROR);
    }

    virtual void GenerateSub(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot subtract two structs", Logger::ERROR);
    }

    virtual void GenerateMul(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot multiply two structs", Logger::ERROR);
    }

    virtual void GenerateDiv(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot divide two structs", Logger::ERROR);
    }

    virtual void GenerateMod(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot modulo two structs", Logger::ERROR);
    }

    virtual void GenerateNot(IVariableLocation* destination, AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot not a struct", Logger::ERROR);
    }

    virtual void GenerateNeg(IVariableLocation* destination, AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot negate a struct", Logger::ERROR);
    }

    virtual void GenerateInc(IVariableLocation* destination, AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot increment a struct", Logger::ERROR);
    }

    virtual void GenerateDec(IVariableLocation* destination, AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot decrement a struct", Logger::ERROR);
    }

    virtual bool CanApplyToThis(Type* other) override
    {
        StructType* otherStruct = dynamic_cast<StructType*>(other);
        if (otherStruct == nullptr) return false;

        // Can be applied if all the properties are the same
        if (properties.Size() != otherStruct->properties.Size()) return false;

        for (size_t i = 0; i < properties.Size(); i++)
        {
            Property thisProperty = this->GetProperty(i);
            Property otherProperty = otherStruct->GetProperty(i);

            if (!thisProperty.type->CanApplyToThis(otherProperty.type)) return false;
            if (!thisProperty.offset == otherProperty.offset) return false;
        }

        return true;
    }

    virtual unsigned int GetSize() override { return size; }
};
#pragma once

#include <string>

#include "../../utils/Logger.cpp"
#include "../../utils/Map.cpp"
#include "../Variable.cpp"
#include "../varLocation/RegistryPointerVarLocation.cpp"
#include "Type.cpp"

class Property
{
   public:
    std::shared_ptr<Type> type;
    unsigned int offset;

    Property(std::shared_ptr<Type> type, unsigned int offset)
    {
        this->type = type;
        this->offset = offset;
    }
    Property() = default;

    std::shared_ptr<Variable> Apply(std::shared_ptr<IVariableLocation> location)
    {
        RegistryPointerVarLocation* newLocation = dynamic_cast<RegistryPointerVarLocation*>(location->Clone());

        if (newLocation == nullptr)
        {
            Logger.Log("Cannot apply property to non-registry pointer location " + location->ToAssemblyString(), Logger::ERROR);
            return nullptr;
        }

        newLocation->IncrementOffset(-offset);

        return std::shared_ptr<Variable>(new Variable(std::shared_ptr<IVariableLocation>(newLocation), type, false));
    }
};

class StructType : public Type
{
   private:
    unsigned int size;
    Map<std::string, Property> properties;

   public:
    StructType() { size = 0; }

    Property AddProperty(std::string name, std::shared_ptr<Type> type)
    {
        Property property = Property(type, size);
        properties.Insert(name, property);
        size += type->GetSize();
        return property;
    }

    Property GetProperty(size_t index) { return properties.At(index).second; }

    std::shared_ptr<Variable> ApplyProperty(std::string name, std::shared_ptr<IVariableLocation> location)
    {
        return properties.Get(name).Apply(location);
    }

    virtual void GenerateAssign(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                                AssemblyCode* assemblyCode) override
    {
        for (size_t i = 0; i < properties.Size(); i++)
        {
            std::string propertyName = properties.At(i).first;

            std::shared_ptr<Variable> destinationProperty = ApplyProperty(propertyName, destination);
            std::shared_ptr<Variable> sourceProperty = ApplyProperty(propertyName, source);

            destinationProperty->type->GenerateAssign(destinationProperty->location, sourceProperty->location, assemblyCode);
        }
    }

    virtual void GenerateAdd(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot add two structs", Logger::ERROR);
    }
    virtual void GenerateSub(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot subtract two structs", Logger::ERROR);
    }
    virtual void GenerateMul(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot multiply two structs", Logger::ERROR);
    }
    virtual void GenerateDiv(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot divide two structs", Logger::ERROR);
    }
    virtual void GenerateMod(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot modulo two structs", Logger::ERROR);
    }

    virtual void GenerateNot(std::shared_ptr<IVariableLocation> destination, AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot not a struct", Logger::ERROR);
    }
    virtual void GenerateNeg(std::shared_ptr<IVariableLocation> destination, AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot negate a struct", Logger::ERROR);
    }
    virtual void GenerateInc(std::shared_ptr<IVariableLocation> destination, AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot increment a struct", Logger::ERROR);
    }
    virtual void GenerateDec(std::shared_ptr<IVariableLocation> destination, AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot decrement a struct", Logger::ERROR);
    }

    virtual void GenerateAnd(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot and two structs", Logger::ERROR);
    }
    virtual void GenerateOr(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                            AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot or two structs", Logger::ERROR);
    }
    virtual void GenerateEqual(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                               AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot compare two structs", Logger::ERROR);
    }
    virtual void GenerateNotEqual(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                                  AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot compare two structs", Logger::ERROR);
    }
    virtual void GenerateLess(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                              AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot compare two structs", Logger::ERROR);
    }
    virtual void GenerateLessEqual(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                                   AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot compare two structs", Logger::ERROR);
    }
    virtual void GenerateGreater(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                                 AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot compare two structs", Logger::ERROR);
    }
    virtual void GenerateGreaterEqual(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                                      AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot compare two structs", Logger::ERROR);
    }

    virtual void GenerateStackPush(std::shared_ptr<IVariableLocation> source, AssemblyCode* assemblyCode) override
    {
        for (size_t i = 0; i < properties.Size(); i++)
        {
            std::string propertyName = properties.At(i).first;
            std::shared_ptr<Variable> property = ApplyProperty(propertyName, source);
            property->type->GenerateStackPush(property->location, assemblyCode);
        }
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

            if (!thisProperty.type->CanApplyToThis(otherProperty.type.get())) return false;
            if (!thisProperty.offset == otherProperty.offset) return false;
        }

        return true;
    }

    virtual unsigned int GetSize() override { return size; }
};
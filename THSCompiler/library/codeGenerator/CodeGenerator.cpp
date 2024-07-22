#pragma once

#include <string>

#include "../assembly/AssemblyCodeGenerator.cpp"
#include "../syntaxTree/nodes/line/expression/operators/EOperators.cpp"
#include "Variable.cpp"
#include "environment/EnvironmentLinkedList.cpp"
#include "types/Type.cpp"
#include "types/primitiveTypes/BoolType.cpp"
#include "types/primitiveTypes/CharType.cpp"
#include "types/primitiveTypes/FloatType.cpp"
#include "types/primitiveTypes/IntType.cpp"
#include "varLocation/RegistryPointerVarLocation.cpp"
#include "varLocation/constVarLocations/BoolConstVarLocation.cpp"
#include "varLocation/constVarLocations/FloatConstVarLocation.cpp"
#include "varLocation/constVarLocations/IntConstVarLocation.cpp"

class CodeGenerator
{
   private:
    EnvironmentLinkedList environmentLinkedList;

    unsigned int localVariableOffset = 0;
    unsigned int parameterOffset = 4;

    void AddPrimitiveTypes()
    {
        AddType("int", std::shared_ptr<Type>(new IntType()));
        AddType("float", std::shared_ptr<Type>(new FloatType()));
        AddType("char", std::shared_ptr<Type>(new CharType()));
        AddType("bool", std::shared_ptr<Type>(new BoolType()));
    }

   public:
    AssemblyCodeGenerator assemblyCodeGenerator = AssemblyCodeGenerator();

    CodeGenerator()
    {
        environmentLinkedList = EnvironmentLinkedList();
        PushNewEnvironment();
        AddPrimitiveTypes();
    }

    bool DoesVariableExist(std::string variableName) { return environmentLinkedList.DoesVariableExist(variableName); }
    std::shared_ptr<Variable> GetVariable(std::string variableName) { return environmentLinkedList.GetVariable(variableName); }
    void AddVariable(std::string variableName, std::shared_ptr<Variable> variable) { environmentLinkedList.AddVariable(variableName, variable); }

    bool DoesFunctionExist(std::string functionName) { return environmentLinkedList.DoesFunctionExist(functionName); }
    std::shared_ptr<Function> GetFunction(std::string functionName) { return environmentLinkedList.GetFunction(functionName); }
    void AddFunction(std::string functionName, std::shared_ptr<Function> function) { environmentLinkedList.AddFunction(functionName, function); }

    bool DoesTypeExist(std::string typeName) { return environmentLinkedList.DoesTypeExist(typeName); }
    std::shared_ptr<Type> GetType(std::string typeName) { return environmentLinkedList.GetType(typeName); }
    void AddType(std::string typeName, std::shared_ptr<Type> type) { environmentLinkedList.AddType(typeName, type); }

    Variable* GetNewRegisterVariable(std::shared_ptr<Type> type, bool isFinal, AssemblyCode* assemblyCode)
    {
        // TODO: Get free register
        return new Variable(std::shared_ptr<IVariableLocation>(new RegistryPointerVarLocation("REGISTER", 0)), type, isFinal);
    }
    Variable* GetNewLocalVariable(std::shared_ptr<Type> type, bool isFinal, AssemblyCode* assemblyCode)
    {
        assemblyCodeGenerator.DecrementRSP(type->GetSize(), assemblyCode);
        RegistryPointerVarLocation* location = new RegistryPointerVarLocation("rbp", -localVariableOffset);
        localVariableOffset += type->GetSize();
        return new Variable(std::shared_ptr<IVariableLocation>(location), type, isFinal);
    }
    void ClearLocalVariableCounter() { localVariableOffset = 0; }
    Variable* GetNewParameterVariable(std::shared_ptr<Type> type, bool isFinal, AssemblyCode* assemblyCode)
    {
        // TODO: Offset from rbp
        IVariableLocation* location = new RegistryPointerVarLocation("rbp", parameterOffset);
        parameterOffset += type->GetSize();
        return new Variable(std::shared_ptr<IVariableLocation>(location), type, isFinal);
    }
    void ClearParameterCounter() { parameterOffset = 4; }

    /// @brief Applies operator on two variables. If both variables are inline then the result is also inline. If only left is inline a new
    /// localVariable will be created and returned.
    /// @return Where the result is stored
    std::shared_ptr<Variable> ApplyOperatorOnVariables(std::shared_ptr<Variable> left, std::shared_ptr<Variable> right, EOperators op,
                                                       AssemblyCode* assemblyCode)
    {
        if (!left->type->CanApplyToThis(right->type.get()))
        {
            Logger.Log("Cannot apply operation in binaryOperatorExpression", Logger::ERROR);
            return nullptr;
        }

        if (left->IsInline())
        {
            if (right->IsInline())
            {
                IConstVarLocation* leftConstLocation = dynamic_cast<IConstVarLocation*>(left->location.get());
                if (leftConstLocation == nullptr)
                {
                    Logger.Log(
                        "Left variable " + right->location->ToAssemblyString() + " is marked as inline but it's variable location is not const",
                        Logger::ERROR);
                    return nullptr;
                }

                IConstVarLocation* rightConstLocation = dynamic_cast<IConstVarLocation*>(right->location.get());
                if (rightConstLocation == nullptr)
                {
                    Logger.Log(
                        "Right variable " + right->location->ToAssemblyString() + " is marked as inline but it's variable location is not const",
                        Logger::ERROR);
                    return nullptr;
                }

                IConstVarLocation* result = nullptr;

                switch (op)
                {
                    case EOperators::ADD_OPERATOR:
                        result = leftConstLocation->GenerateAdd(rightConstLocation);
                        break;
                    case EOperators::SUB_OPERATOR:
                        result = leftConstLocation->GenerateSub(rightConstLocation);
                        break;
                    case EOperators::MUL_OPERATOR:
                        result = leftConstLocation->GenerateMul(rightConstLocation);
                        break;
                    case EOperators::DIV_OPERATOR:
                        result = leftConstLocation->GenerateDiv(rightConstLocation);
                        break;
                    case EOperators::MOD_OPERATOR:
                        result = leftConstLocation->GenerateMod(rightConstLocation);
                        break;
                    case EOperators::AND_OPERATOR:
                        result = leftConstLocation->GenerateAnd(rightConstLocation);
                        break;
                    case EOperators::OR_OPERATOR:
                        result = leftConstLocation->GenerateOr(rightConstLocation);
                        break;
                    case ::EOperators::EQUAL_OPERATOR:
                        result = leftConstLocation->GenerateEqual(rightConstLocation);
                        break;
                    case EOperators::NOT_EQUAL_OPERATOR:
                        result = leftConstLocation->GenerateNotEqual(rightConstLocation);
                        break;
                    case EOperators::LESS_THAN_OPERATOR:
                        result = leftConstLocation->GenerateLess(rightConstLocation);
                        break;
                    case EOperators::LESS_THAN_OR_EQUAL_OPERATOR:
                        result = leftConstLocation->GenerateLessEqual(rightConstLocation);
                        break;
                    case EOperators::GREATER_THAN_OPERATOR:
                        result = leftConstLocation->GenerateGreater(rightConstLocation);
                        break;
                    case EOperators::GREATER_THAN_OR_EQUAL_OPERATOR:
                        result = leftConstLocation->GenerateGreaterEqual(rightConstLocation);
                        break;
                }

                return std::shared_ptr<Variable>(new Variable(std::shared_ptr<IVariableLocation>(result), left->type, true));
            }
            else
            {
                Variable* newLocalVariable = GetNewLocalVariable(left->type, false, assemblyCode);
                left->type->GenerateAssign(newLocalVariable->location.get(), right->location.get(), assemblyCode);
                left = std::shared_ptr<Variable>(newLocalVariable);
            }
        }

        switch (op)
        {
            case EOperators::ADD_OPERATOR:
                left->type->GenerateAdd(left->location.get(), right->location.get(), assemblyCode);
                break;
            case EOperators::SUB_OPERATOR:
                left->type->GenerateSub(left->location.get(), right->location.get(), assemblyCode);
                break;
            case EOperators::MUL_OPERATOR:
                left->type->GenerateMul(left->location.get(), right->location.get(), assemblyCode);
                break;
            case EOperators::DIV_OPERATOR:
                left->type->GenerateDiv(left->location.get(), right->location.get(), assemblyCode);
                break;
            case EOperators::MOD_OPERATOR:
                left->type->GenerateMod(left->location.get(), right->location.get(), assemblyCode);
                break;
            case EOperators::AND_OPERATOR:
                left->type->GenerateAnd(left->location.get(), right->location.get(), assemblyCode);
                break;
            case EOperators::OR_OPERATOR:
                left->type->GenerateOr(left->location.get(), right->location.get(), assemblyCode);
                break;
            case ::EOperators::EQUAL_OPERATOR:
                left->type->GenerateEqual(left->location.get(), right->location.get(), assemblyCode);
                break;
            case EOperators::NOT_EQUAL_OPERATOR:
                left->type->GenerateNotEqual(left->location.get(), right->location.get(), assemblyCode);
                break;
            case EOperators::LESS_THAN_OPERATOR:
                left->type->GenerateLess(left->location.get(), right->location.get(), assemblyCode);
                break;
            case EOperators::LESS_THAN_OR_EQUAL_OPERATOR:
                left->type->GenerateLessEqual(left->location.get(), right->location.get(), assemblyCode);
                break;
            case EOperators::GREATER_THAN_OPERATOR:
                left->type->GenerateGreater(left->location.get(), right->location.get(), assemblyCode);
                break;
            case EOperators::GREATER_THAN_OR_EQUAL_OPERATOR:
                left->type->GenerateGreaterEqual(left->location.get(), right->location.get(), assemblyCode);
                break;
        }

        return left;
    }

    IVariableLocation* ConstructLogicalConstVariableLocation(bool value) { return new BoolConstVarLocation(value); }
    IVariableLocation* ConstructIntConstVariableLocation(int value) { return new IntConstVarLocation(value); }
    IVariableLocation* ConstructFloatConstVaribaleLocation(float value) { return new FloatConstVarLocation(value); }

    void PushNewEnvironment() { environmentLinkedList.PushEnvironment(new Environment()); }
    void PopEnvironment() { environmentLinkedList.PopEnvironment(); }
};
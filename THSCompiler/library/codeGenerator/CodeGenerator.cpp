#pragma once

#include <string>

#include "../syntaxTree/nodes/line/expression/operators/EOperators.cpp"
#include "Variable.cpp"
#include "environment/EnvironmentLinkedList.cpp"
#include "types/Type.cpp"
#include "types/primitiveTypes/BoolType.cpp"
#include "types/primitiveTypes/CharType.cpp"
#include "types/primitiveTypes/FloatType.cpp"
#include "types/primitiveTypes/IntType.cpp"
#include "varLocation/constVarLocations/BoolConstVarLocation.cpp"
#include "varLocation/constVarLocations/FloatConstVarLocation.cpp"
#include "varLocation/constVarLocations/IntConstVarLocation.cpp"

class CodeGenerator
{
   private:
    EnvironmentLinkedList environmentLinkedList;

    void AddPrimitiveTypes()
    {
        AddType("int", std::shared_ptr<Type>(new IntType()));
        AddType("float", std::shared_ptr<Type>(new FloatType()));
        AddType("char", std::shared_ptr<Type>(new CharType()));
        AddType("bool", std::shared_ptr<Type>(new BoolType()));
    }

   public:
    CodeGenerator()
    {
        environmentLinkedList = EnvironmentLinkedList();
        PushNewEnvironment();
        AddPrimitiveTypes();
    }

    bool DoesVariableExist(std::string variableName) { return environmentLinkedList.DoesVariableExist(variableName); }
    std::shared_ptr<Variable> GetVariable(std::string variableName) { return environmentLinkedList.GetVariable(variableName); }
    void AddVariable(std::string variableName, std::shared_ptr<Variable> variable) { environmentLinkedList.AddVariable(variableName, variable); }

    bool DoesTypeExist(std::string typeName) { return environmentLinkedList.DoesTypeExist(typeName); }
    std::shared_ptr<Type> GetType(std::string typeName) { return environmentLinkedList.GetType(typeName); }
    void AddType(std::string typeName, std::shared_ptr<Type> type) { environmentLinkedList.AddType(typeName, type); }

    Variable* GetNewLocalVariable(std::shared_ptr<Type> type, bool isFinal, AssemblyCode* assemblyCode) { return nullptr; }

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
                // TODO: Inline operation
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
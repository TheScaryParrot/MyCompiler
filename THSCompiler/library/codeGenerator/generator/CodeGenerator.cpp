#pragma once

#include <memory>

#include "../environment/scopeSpecificEnvironments/environmentLinkedList/ScopeSpecificEnvironmentLinkedList.cpp"
#include "../environment/scopeSpecificEnvironments/GlobalScopeEnvironment.cpp"
#include "../environment/scopeSpecificEnvironments/FunctionScopeEnvironment.cpp"

#include "../../assembly/AssemblyCode.cpp"
#include "../../assembly/AssemblyLabelLine.cpp"
#include "../../assembly/AssemblyInstructionLine.cpp"
#include "../../assembly/instructions/AssemblyInstructions.cpp"

class CodeGenerator
{
public:
    CodeGenerator();

    Variable* AddVariable(std::string name, std::string typeIdentifier);
    AssemblyCode* SetVariable(std::string variableName, IVariableLocationGetter* assignValueLocation);

    Function* AddFunction(std::string name, std::string returnTypeIdentifier /*TODO: Add parameters*/);
    AssemblyCode* SetFunctionBody(Function* function, AssemblyCode* body);

    AssemblyCode* GenerateReturnStatement(AssemblyCode* expression);
    AssemblyCode* GenerateContinueStatement();
    AssemblyCode* GenerateBreakStatement();

    void InitLoopEnvironment();
    AssemblyCode* GenerateWhile(AssemblyCode* condition, AssemblyCode* body);
    AssemblyCode* GenrateFor(AssemblyCode* declaration, AssemblyCode* condition, AssemblyCode* increment, AssemblyCode* body);

private:
    ScopeSpecificEnvironmentLinkedList environmentLinkedList;

    ScopeSpecificEnvironmentLinkedListElement* GetCurrentEnvironment();

    unsigned int jumpLabelCounter = 0;

    std::string GetNewJumpLabel();
    JumpLabel* AddJumpLabel(std::string name);
    AssemblyCode* GenerateLabel(JumpLabel* jumpLabel);
    AssemblyCode* GenerateJumpToLabel(JumpLabel* jumpLabel);
};

CodeGenerator::CodeGenerator()
{
    environmentLinkedList = ScopeSpecificEnvironmentLinkedList();
    environmentLinkedList.PushEnvironment(std::make_shared<GlobalScopeEnvironment>());
}


ScopeSpecificEnvironmentLinkedListElement* CodeGenerator::GetCurrentEnvironment()
{
    return environmentLinkedList.GetHead();
}

Variable* CodeGenerator::AddVariable(std::string name, std::string typeIdentifier)
{
    Type* type = GetCurrentEnvironment()->GetType(typeIdentifier);
    
    Variable* variable = new Variable(type);

    GetCurrentEnvironment()->AddVariable(name, variable);

    return variable;
}

AssemblyCode* CodeGenerator::SetVariable(std::string variableName, IVariableLocationGetter* assignValueLocation)
{
    //TODO: Assign variable
    return nullptr;
}

Function* CodeGenerator::AddFunction(std::string name, std::string returnTypeIdentifier)
{
    Type* returnType = GetCurrentEnvironment()->GetType(returnTypeIdentifier);

    // TODO: Construct parameters from type and name; requires locationGetter and locationSetter
    Function* function = new Function(returnType); // TODO: Add parameters

    GetCurrentEnvironment()->AddFunction(name, function);
}

AssemblyCode* CodeGenerator::SetFunctionBody(Function* function, AssemblyCode* body)
{
    return GetCurrentEnvironment()->SetFunctionBody(function, body);
}

AssemblyCode* CodeGenerator::GenerateReturnStatement(AssemblyCode* expression)
{
    AssemblyCode* assemblyCode = new AssemblyCode();
    // TODO: Get return variable
    assemblyCode->AddLines(this->SetVariable("return", nullptr));
    assemblyCode->AddLine(std::make_shared<AssemblyInstructionLine>(AssemblyInstructions::RET));
    return assemblyCode;
}

AssemblyCode* CodeGenerator::GenerateContinueStatement()
{
    return GenerateJumpToLabel(GetCurrentEnvironment()->GetJumpLabel("continue"));
}

AssemblyCode* CodeGenerator::GenerateBreakStatement()
{
    return GenerateJumpToLabel(GetCurrentEnvironment()->GetJumpLabel("break"));
}

void CodeGenerator::InitLoopEnvironment()
{
    environmentLinkedList.PushEnvironment(std::make_shared<FunctionScopeEnvironment>());
    AddJumpLabel("continue"); // eval label
    AddJumpLabel("break"); // final label
}

AssemblyCode* CodeGenerator::GenerateWhile(AssemblyCode* condition, AssemblyCode* body)
{
    AssemblyCode* assemblyCode = new AssemblyCode();

    JumpLabel* continueLabel = GetCurrentEnvironment()->GetJumpLabel("continue");
    JumpLabel* breakLabel = GetCurrentEnvironment()->GetJumpLabel("break");

    assemblyCode->AddLines(GenerateLabel(continueLabel)); // eval label
    assemblyCode->AddLines(condition); // condition
    
    //TODO: Add jump to break label if condition is false
    assemblyCode->AddLines(body); // body

    assemblyCode->AddLines(GenerateJumpToLabel(continueLabel));

    assemblyCode->AddLines(GenerateLabel(breakLabel));

    environmentLinkedList.PopEnvironment();

    return assemblyCode;
}

AssemblyCode* CodeGenerator::GenrateFor(AssemblyCode* declaration, AssemblyCode* condition, AssemblyCode* increment, AssemblyCode* body)
{

} 

std::string CodeGenerator::GetNewJumpLabel()
{
    return "JL" + std::to_string(jumpLabelCounter++);
}

JumpLabel* CodeGenerator::AddJumpLabel(std::string name)
{
    JumpLabel* jumpLabel = new JumpLabel(GetNewJumpLabel());

    GetCurrentEnvironment()->AddJumpLabel(name, jumpLabel);

    return jumpLabel;
}

AssemblyCode* CodeGenerator::GenerateLabel(JumpLabel* jumpLabel)
{
    AssemblyCode* assemblyCode = new AssemblyCode();
    assemblyCode->AddLine(std::make_shared<AssemblyLabelLine>(jumpLabel->GetName()));
    return assemblyCode;
};

AssemblyCode* CodeGenerator::GenerateJumpToLabel(JumpLabel* jumpLabel)
{
    AssemblyCode* assemblyCode = new AssemblyCode();
    AssemblyInstructionLine* jumpLine = (new AssemblyInstructionLine(AssemblyInstructions::JMP))->AddArgument(jumpLabel->GetName());
    assemblyCode->AddLine(std::shared_ptr<AssemblyInstructionLine>(jumpLine));
    return assemblyCode;
};

#pragma once

#include "../utils/Logger.cpp"
#include "Environment.cpp"

class InstructionEnvironment : private Environment
{
   public:
    InstructionEnvironment();

    void ExecuteInstruction(std::string name, ICodeGenerator* codeGenerator);
    Callable* GetInstruction(std::string name);
};

InstructionEnvironment::InstructionEnvironment()
{
    this->AddCallable("debug",
                      new Callable([](ICodeGenerator* generator) { Logger.Log("DEBUG PRINT", Logger::INFO); }));
};

void InstructionEnvironment::ExecuteInstruction(std::string name, ICodeGenerator* codeGenerator)
{
    this->ExecuteCallable(name, codeGenerator);
}

Callable* InstructionEnvironment::GetInstruction(std::string name) { return this->GetCallable(name); }
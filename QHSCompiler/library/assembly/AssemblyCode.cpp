#pragma once

#include <string>

class AssemblyCode
{
   public:
    void AddCode(std::string code);
    void AddCode(AssemblyCode* code);

    std::string GetCode();
    std::string ToString();

   private:
    std::string code = "";
};

void AssemblyCode::AddCode(std::string code) { this->code += code; }

void AssemblyCode::AddCode(AssemblyCode* code) { AddCode(code->GetCode()); }

std::string AssemblyCode::GetCode() { return code; }

std::string AssemblyCode::ToString() { return "---- AssemblyCode ----\n" + GetCode(); }

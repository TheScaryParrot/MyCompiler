#pragma once

#include <memory>
#include <string>
#include <vector>

#include "IAssemblyLine.cpp"

class AssemblyCode
{
   public:
    AssemblyCode* AddLine(IAssemblyLine* line);
    AssemblyCode* AddLines(AssemblyCode* code);

    std::vector<IAssemblyLine*>& GetLines();
    std::string ToString();

   private:
    std::vector<IAssemblyLine*> lines = std::vector<IAssemblyLine*>();
};

AssemblyCode* AssemblyCode::AddLine(IAssemblyLine* line)
{
    if (line == nullptr) return this;

    this->lines.push_back(line);
    return this;
}

AssemblyCode* AssemblyCode::AddLines(AssemblyCode* code)
{
    if (code == nullptr) return this;

    for (auto& line : code->GetLines())
    {
        if (line == nullptr) continue;

        this->lines.push_back(line);
    }

    return this;
}

std::vector<IAssemblyLine*>& AssemblyCode::GetLines() { return lines; }

std::string AssemblyCode::ToString()
{
    std::string result;

    for (auto& line : lines)
    {
        result += line->ToString() + "\n";
    }

    return result;
}
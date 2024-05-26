#pragma once

#include <string>
#include <vector>
#include <memory>

#include "IAssemblyLine.cpp"

class AssemblyCode
{
public:
    AssemblyCode* AddLine(std::shared_ptr<IAssemblyLine> line);
    AssemblyCode* AddLines(std::shared_ptr<AssemblyCode> code);

    std::vector<std::shared_ptr<IAssemblyLine>> GetLines();
    std::string ToString();

private:
    std::vector<std::shared_ptr<IAssemblyLine>> lines;
};

AssemblyCode* AssemblyCode::AddLine(std::shared_ptr<IAssemblyLine> line)
{
    lines.push_back(line);
    return this;
}

AssemblyCode* AssemblyCode::AddLines(std::shared_ptr<AssemblyCode> code)
{
    for (std::shared_ptr<IAssemblyLine>& line : code->GetLines())
    {
        lines.push_back(line);
    }

    return this;
}

std::vector<std::shared_ptr<IAssemblyLine>> AssemblyCode::GetLines()
{
    return lines;
}

std::string AssemblyCode::ToString()
{
    std::string result;
    
    for (std::shared_ptr<IAssemblyLine>& line : lines)
    {
        result += line->ToString() + "\n";
    }

    return result;
}
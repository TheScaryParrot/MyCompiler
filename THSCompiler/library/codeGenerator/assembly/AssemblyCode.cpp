#pragma once

#include <string>
#include <vector>
#include <memory>

#include "IAssemblyLine.cpp"

class AssemblyCode
{
public:
    AssemblyCode* AddLine(std::auto_ptr<IAssemblyLine> line);

    std::string ToString();

private:
    std::vector<std::auto_ptr<IAssemblyLine>> lines;
};

AssemblyCode* AssemblyCode::AddLine(std::auto_ptr<IAssemblyLine> line)
{
    lines.push_back(line);
    return this;
}

std::string AssemblyCode::ToString()
{
    std::string result;
    
    for (std::auto_ptr<IAssemblyLine>& line : lines)
    {
        result += line->ToString() + "\n";
    }

    return result;
}
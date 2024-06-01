#pragma once

#include "IAssemblyLine.cpp"

class AssemblyLabelLine : public IAssemblyLine
{
public:
    AssemblyLabelLine(std::string label);

    std::string ToString() override;

private:
    std::string label;
};

AssemblyLabelLine::AssemblyLabelLine(std::string label)
{
    this->label = label;
}

std::string AssemblyLabelLine::ToString()
{
    return label + ":";
}
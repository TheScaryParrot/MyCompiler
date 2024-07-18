#pragma once

#include "IAssemblyLine.cpp"

class AssemblyLabelLine : public IAssemblyLine
{
   public:
    AssemblyLabelLine(std::string label) { this->label = label; };

    std::string ToString() override { return label + ":"; };

   private:
    std::string label;
};
#pragma once

#include <memory>
#include <string>
#include <vector>

#include "DataDeclarationLine.cpp"
#include "IAssemblyLine.cpp"

class AssemblyCode
{
   public:
    void AddLine(IAssemblyLine* line)
    {
        if (line == nullptr) return;

        this->text.push_back(line);
    }

    void AddToRoData(DataDeclarationLine* line)
    {
        if (line == nullptr) return;

        this->roData.push_back(line);
    }

    void AddToData(DataDeclarationLine* line)
    {
        if (line == nullptr) return;

        this->data.push_back(line);
    }

    std::string ToString()
    {
        std::string result = "";

        for (auto& line : text)
        {
            result += line->ToString() + "\n";
        }

        return result;
    };

   private:
    std::vector<IAssemblyLine*> text = std::vector<IAssemblyLine*>();
    std::vector<DataDeclarationLine*> roData = std::vector<DataDeclarationLine*>();
    std::vector<DataDeclarationLine*> data = std::vector<DataDeclarationLine*>();
};
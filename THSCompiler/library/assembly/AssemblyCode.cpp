#pragma once

#include <memory>
#include <string>
#include <vector>

#include "DataDeclarationLine.cpp"
#include "IAssemblyLine.cpp"

class AssemblyCode
{
   public:
    ~AssemblyCode()
    {
        for (auto& line : text)
        {
            delete line;
        }

        for (auto& line : roData)
        {
            delete line;
        }

        for (auto& line : data)
        {
            delete line;
        }
    }

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

        result += "global main\n";

        result += "\nsection .text\n";
        for (auto& line : text)
        {
            result += line->ToString() + "\n";
        }

        if (data.size() > 0)
        {
            result += "\nsection .data\n";
            for (auto& line : data)
            {
                result += line->ToString() + "\n";
            }
        }

        if (roData.size() > 0)
        {
            result += "\nsection .rodata\n";
            for (auto& line : roData)
            {
                result += line->ToString() + "\n";
            }
        }

        return result;
    };

   private:
    std::vector<IAssemblyLine*> text = std::vector<IAssemblyLine*>();
    std::vector<DataDeclarationLine*> roData = std::vector<DataDeclarationLine*>();
    std::vector<DataDeclarationLine*> data = std::vector<DataDeclarationLine*>();
};
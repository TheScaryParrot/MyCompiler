#pragma once

#include <string>

class VariableLocation
{
   public:
    VariableLocation(std::string base, int offset);

    std::string GetBase();
    void SetBase(std::string base);

    int GetOffset();
    void SetOffset(int offset);
    /// @brief Adds increment to the offset; increment can be negative
    void IncrementOffset(int increment);

   private:
    std::string base;
    int offset;
};

VariableLocation::VariableLocation(std::string base, int offset)
{
    this->base = base;
    this->offset = offset;
}

std::string VariableLocation::GetBase() { return base; }

void VariableLocation::SetBase(std::string base) { this->base = base; }

int VariableLocation::GetOffset() { return offset; }

void VariableLocation::SetOffset(int offset) { this->offset = offset; }

void VariableLocation::IncrementOffset(int increment) { offset += increment; }
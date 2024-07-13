#pragma once

#include <string>

#include "Type.cpp"

class VariableLocation
{
   public:
    VariableLocation(std::string base, int offset, Type* type);

    std::string GetBase();
    void SetBase(std::string base);
    bool IsBaseEmpty();

    int GetOffset();
    void SetOffset(int offset);
    /// @brief Adds increment to the offset; increment can be negative
    void IncrementOffset(int increment);

    Type* GetType();
    void SetType(Type* type);

   private:
    std::string base;
    int offset;
    Type* type;
};

VariableLocation::VariableLocation(std::string base, int offset, Type* type)
{
    this->base = base;
    this->offset = offset;
    this->type = type;
}

std::string VariableLocation::GetBase() { return base; }

void VariableLocation::SetBase(std::string base) { this->base = base; }

bool VariableLocation::IsBaseEmpty() { return base.empty(); }

int VariableLocation::GetOffset() { return offset; }

void VariableLocation::SetOffset(int offset) { this->offset = offset; }

void VariableLocation::IncrementOffset(int increment) { offset += increment; }

Type* VariableLocation::GetType() { return type; }
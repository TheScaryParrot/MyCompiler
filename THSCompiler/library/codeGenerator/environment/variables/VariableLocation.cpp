#pragma once

#include <string>

class VariableLocation
{
public:
    VariableLocation();
    VariableLocation(std::string originMemoryLocation, int offset);

    void SetOriginMemoryLocation(std::string originMemoryLocation);
    void SetOffset(int offset);
    void AddToOffset(int offset);

    std::string ToString();

private:
    /// @brief String referring to the memory location of the variable
    std::string originMemoryLocation;

    /// @brief Offset from the origin memory location
    int offset;
};

VariableLocation::VariableLocation()
{
    this->originMemoryLocation = "";
    this->offset = 0;
}

VariableLocation::VariableLocation(std::string originMemoryLocation, int offset)
{
    this->originMemoryLocation = originMemoryLocation;
    this->offset = offset;
}

void VariableLocation::SetOriginMemoryLocation(std::string originMemoryLocation)
{
    this->originMemoryLocation = originMemoryLocation;
}

void VariableLocation::SetOffset(int offset)
{
    this->offset = offset;
}

void VariableLocation::AddToOffset(int offset)
{
    this->offset += offset;
}

std::string VariableLocation::ToString()
{
    //TODO: Check if this is the correct format
    return "[" + originMemoryLocation + " + " + std::to_string(offset) + "]";
}
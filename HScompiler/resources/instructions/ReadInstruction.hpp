#include "../CustomInstructionBase.hpp"

class ReadInstruction : public CustomInstructonBase
{
public:
    ReadInstruction() : CustomInstructonBase("read", 2) {}

    virtual std::string GetAssemblyCode(unsigned int line, std::string precedingSpaces, std::vector<std::string> arguments, std::string comment) override;

    bool CheckValidUsage(unsigned int line, std::vector<std::string> arguments, std::string comment);

    bool IsLineCustomInstruction(std::string line);
};
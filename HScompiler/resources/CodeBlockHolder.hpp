#include <string>

/// @brief Utility for creating code blocks. Contains utility like AddLine, etc.
class CodeBlockHolder
{
private:
    std::string precedingSpaces;

    std::string codeString = "";

public:
    CodeBlockHolder(std::size_t precedingSpacesCount);
    CodeBlockHolder(std::string precedingSpaces);

    void AddLine(std::string line);

    std::string GetString();
};
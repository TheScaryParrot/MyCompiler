#include <iostream>
#include <fstream>

#include "resources/instructions/PrintInstruction.cpp"
#include "resources/Helper.cpp"

CustomInstructonBase* CUSTOM_INSTRUCTIONS[] = {
    new PrintInstruction()
};

CustomInstructonBase* GetCustomInstruction(std::string line)
{
    for (CustomInstructonBase* customInstruction :  CUSTOM_INSTRUCTIONS)
    {
        if (customInstruction->IsLineCustomInstruction(line))
        {
            return customInstruction;
        }
    }

    return nullptr;
}

void CompileFile(std::ifstream* inputFile, std::ofstream* outputFile)
{
    std::string line;
    int lineNumber = 1;
    
    while (!inputFile->eof() && inputFile->good())
    {
        std::getline(*inputFile, line); // Reads line from inputFile into line

        CustomInstructonBase* customInstruction = GetCustomInstruction(line);

        if (customInstruction != nullptr)
        {
            std::vector<std::string> arguments = GetArguments(line);
            std::string comment = GetComment(line);
            std::string precidingSpaces = GetPrecedingSpaces(line);

            if (!customInstruction->CheckValidUsage(lineNumber, arguments, comment))
            {
                // Error printing is handled by CheckValidUsage
                return;
            }

            *outputFile << customInstruction->GetAssemblyCode(lineNumber, precidingSpaces, arguments, comment) << "\n";
        }
        else
        {
            *outputFile << line << "\n";
        }

        lineNumber++;
    }
}

int main(int argc, char* argv[])
{
    std::cout << "Hello from the HScompiler\n";
    
    if (argc < 2)
    {
        std::cout << "No input file specified\n";
        return 1;
    }
    if (argc > 2)
    {
        std::cout << "More than one argument was specified\nOnly the first argument will be used\n";
    }
    
    std::ifstream inputFile(argv[1]);
    std::ofstream outputFile("output.s");

    if (!inputFile.is_open())
    {
        std::cout << "Could not open input file\n";
        return 1;
    }

    if (!outputFile.is_open())
    {
        std::cout << "Could not open output file\n";
        return 1;
    }

    CompileFile(&inputFile, &outputFile);

    return 0;
}
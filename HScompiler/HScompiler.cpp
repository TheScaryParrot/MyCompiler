#include <iostream>
#include <fstream>

#include "resources/instructions/PrintInstruction.cpp"
#include "resources/instructions/ReadInstruction.cpp"
#include "resources/instructions/ExitInstruction.cpp"
#include "resources/Helper.cpp"

CustomInstructonBase* CUSTOM_INSTRUCTIONS[] = {
    new PrintInstruction(),
    new ReadInstruction(),
    new ExitInstruction()
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

/// @brief Exectures the compiler
/// @param inputFilePath Path to the file to compile
/// @param outputFilePath Path to the file to output to
/// @param compileToExe Whether to compile all the way to an executable
void Execute(std::string inputFilePath, std::string outputFilePath, bool compileToExe)
{
    // INPUT FILE
    if (inputFilePath == "")
    {
        std::cout << "inputFilePath is null\n";
        return;
    }

    std::ifstream inputFile(inputFilePath);

    if (!inputFile.is_open())
    {
        std::cout << "Could not open input file\n";
        return;
    }


    // OUTPUT FILE
    if (outputFilePath == "")
    {
        outputFilePath = "output.s";
    }

    std::ofstream outputFile(outputFilePath);

    if (!outputFile.is_open())
    {
        std::cout << "Could not open output file\n";
        return;
    }

    // COMPILATION
    CompileFile(&inputFile, &outputFile);

    /*if (compileToExe)
    {
        std::string objectFilePath = outputFilePath + ".o";
        system(std::string("nasm -f elf64 " + assemblyFilePath + " -o " + objectFilePath).c_str()); //command = "nasm -f elf64 OUTFILE -o OUTFILE.o"

        std::string exeFilePath = outputFilePath;
        system(std::string("ld " + objectFilePath + " -o " + outputFilePath).c_str()); //command = "ld OUTFILE.o -o OUTFILE"

        // Remove the object file and assembly file
        //system(std::string("rm " + objectFilePath).c_str()); //command = "rm OUTFILE.o"
        //system(std::string("rm " + assemblyFilePath).c_str()); //command = "rm OUTFILE.s"
    }*/
}

int main(int argc, char* argv[])
{
    std::cout << "Hello from the HScompiler\n";
    
    if (argc < 2)
    {
        std::cout << "No input file specified\n";
        return 1;
    }

    std::string inputFile = argv[1];

    int currentArgIndex = 2;
    std::string outputFile = "";
    bool compileToExe = false;

    while (currentArgIndex < argc)
    {
        std::string arg = argv[currentArgIndex];

        if (arg == "-o")
        {
            // If this is the last argument
            if (argc < currentArgIndex + 2)
            {
                std::cout << "No output file specified\n";
                return 1;
            }

            outputFile = argv[currentArgIndex + 1];

            currentArgIndex += 2;
        }
        else if (arg == "-c")
        {
            compileToExe = true;
            currentArgIndex++;
        }
        
        else
        {
            std::cout << "Unknown argument: " << arg << "\n";
            return 1;
        }
    }
    
    Execute(inputFile, outputFile, compileToExe);

    return 0;
}
#include <iostream>
#include <fstream>

#include "resources/instructions/PrintInstruction.cpp"
#include "resources/instructions/ReadInstruction.cpp"
#include "resources/instructions/ExitInstruction.cpp"
#include "resources/Helper.cpp"

const std::string HELP_TEXT = 
    "HScompiler\n"
    "Usage: HScompiler [INPUT_FILE] [OPTIONS]\n"
    "Options:\n"
    "    -o [OUTPUT_FILE]    Specify the output file. If not used the output file will be named output\n"
    "    -c                  Compile to an executable\n"
    "    -k                  Keep temporary files\n"
    "    -h                  Display this help text\n";

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

void CompileFile(std::string inputFileDirectory, std::ifstream* inputFile, std::ofstream* outputFile)
{
    std::string line;
    int lineNumber = 1;
    
    while (!inputFile->eof() && inputFile->good())
    {
        std::getline(*inputFile, line); // Reads line from inputFile into line

        if (GetInstructionName(line) == "include")
        {
            std::vector<std::string> arguments = GetArguments(line);

            if (arguments.size() < 2)
            {
                std::cout << "Invalid usage of include on line " << lineNumber << ". Missing argument\n";
                return;
            }

            bool isAbsolutePath = false;
            
            if (arguments[0] == "absolute")
            {
                isAbsolutePath = true;
            }
            else if (arguments[0] != "relative")
            {
                std::cout << "Invalid usage of include on line " << lineNumber << ". First argument must be 'absolute' or 'relative'\n";
                return;
            }
            
            std::string includeFilePath = isAbsolutePath ? arguments[1] : inputFileDirectory + arguments[1];

            std::ifstream* includeFile = new std::ifstream(includeFilePath);

            if (!includeFile->is_open())
            {
                std::cout << "Could not open include file " << includeFilePath << " on line " << lineNumber << "\n";
                return;
            }

            CompileFile(inputFileDirectory, includeFile, outputFile);

            includeFile->close();
            delete includeFile;

            continue;
        }

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
void Execute(std::string inputFilePath, std::string outputFilePath, bool compileToExe, bool keepTemporaries)
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
    std::string assemblyFilePath;
    std::string objectFilePath;
    std::string exeFilePath;

    if (compileToExe)
    {
        if (outputFilePath == "")
        {
            outputFilePath = "output";
        }

        assemblyFilePath = outputFilePath + ".s";
        objectFilePath = outputFilePath + ".o";
        exeFilePath = outputFilePath;
    }
    else
    {
        if (outputFilePath == "")
        {
            outputFilePath = "output.s";
        }

        assemblyFilePath = outputFilePath;
    }
    

    std::ofstream outputFile(assemblyFilePath);

    if (!outputFile.is_open())
    {
        std::cout << "Could not open output file\n";
        return;
    }

    // COMPILATION
    CompileFile(GetDirectoryPath(inputFilePath), &inputFile, &outputFile);

    inputFile.close();
    outputFile.close(); // Important to close the file before compiling to an executable. As otherwise an empty file will be compiled

    if (compileToExe)
    {
        // Compile to an executable
        std::string nasmCommand = "nasm -f elf64 " + assemblyFilePath + " -o " + objectFilePath;
        std::system(nasmCommand.c_str()); //command = "nasm -f elf64 OUTFILE -o OUTFILE.o"

        std::string linkCommand = "ld " + objectFilePath + " -o " + exeFilePath; 
        std::system(linkCommand.c_str()); //command = "ld OUTFILE.o -o OUTFILE"

        if (keepTemporaries) return;

        // Remove the object file and assembly file
        std::system(std::string("rm " + assemblyFilePath).c_str()); //command = "rm OUTFILE.s"
        std::system(std::string("rm " + objectFilePath).c_str()); //command = "rm OUTFILE.o"
    }
}

void PrintHelpText()
{
    std::cout << HELP_TEXT;
}

int main(int argc, char* argv[])
{
    std::cout << "Hello from the HScompiler\n";
    
    if (argc < 2)
    {
        std::cout << "No input file specified. Use -h for help\n";
        return 1;
    }

    
    int currentArgIndex = 1;
    std::string inputFile = "";
    std::string outputFile = "";
    bool compileToExe = false;
    bool keepTemporaries = false;

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
        else if (arg == "-k")
        {
            keepTemporaries = true;
            currentArgIndex++;
        }
        else if (arg == "-h")
        {
            PrintHelpText();
            return 0;
        }
        else if (inputFile == "")
        {
            inputFile = arg;
            currentArgIndex++;
        }
        else
        {
            std::cout << "Unknown argument: " << arg << ". Use -h for help\n";
            return 1;
        }
    }
    
    Execute(inputFile, outputFile, compileToExe, keepTemporaries);

    return 0;
}
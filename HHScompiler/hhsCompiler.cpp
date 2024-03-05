#include <iostream>
#include <string>

#include "library/InputFile.cpp"
#include "library/CompilationHandler.cpp"

void CompileFile(InputFile* file)
{
    while (file->IsGood())
    {
        std::cout << CompilationHandler.Compile(file->GetNextLine()) << "\n";
    }
}

void Execute(std::string inputFileName)
{
    InputFile* inputFile = new InputFile(inputFileName);

    if (!inputFile->IsOpen())
    {
        std::cout << "Error: Could not open file " << inputFileName << "\n";
        return;
    }

    CompileFile(inputFile);
}


const std::string HELP_TEXT = "Usage: hhsCompiler [options] <file>\n";

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        std::cout << HELP_TEXT;
        return 1;
    }

    std::string inputFileName;

    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help")
        {
            std::cout << HELP_TEXT;
            return 0;
        }
        else
        {
            inputFileName = arg;
        }
    }

    Execute(inputFileName);

    return 0;
}

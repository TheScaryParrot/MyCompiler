#include <iostream>
#include <string>

#include "library/FileParsingHelper.cpp"

std::string CompileLine(std::string line)
{

}

void CompileFile(std::ifstream* file)
{
    while (file->good())
    {
        std::string line = FileParsingHelper.GetNextLine(file);
        std::cout << CompileLine(line) << "\n";
    }
}

void Execute(std::string inputFileName)
{
    std::ifstream file(inputFileName);

    if (!file.is_open())
    {
        std::cout << "Error: Could not open file " << inputFileName << "\n";
        return;
    }

    CompileFile(&file);
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

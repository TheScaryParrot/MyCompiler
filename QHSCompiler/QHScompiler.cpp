#include <iostream>

#include "library/InputFile.cpp"
#include "library/codeGenerator/Generator.cpp"

void CompileFile(std::string filename)
{
    InputFile* file = new InputFile(filename);

    Generator generator = Generator(file);

    AssemblyCode* assemblyCode = generator.Generate();

    delete file;

    std::cout << assemblyCode->ToString() << "\n";

    delete assemblyCode;
}

int main(int argc, char const* argv[])
{
    CompileFile(argv[1]);
    return 0;
}

#include <iostream>

#include "library/InputFile.cpp"
#include "library/codeGenerator/CodeGenerator.cpp"

void CompileFile(std::string filename)
{
    InputFile* file = new InputFile(filename);

    CodeGenerator codeGenerator = CodeGenerator();

    AssemblyCode* assemblyCode = codeGenerator.Generate(file);

    delete file;

    std::cout << assemblyCode->ToString() << "\n";
}

int main(int argc, char const* argv[])
{
    CompileFile(argv[1]);
    return 0;
}

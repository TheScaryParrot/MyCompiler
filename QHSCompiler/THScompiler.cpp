#include <iostream>

#include "library/InputFile.cpp"
#include "library/codeGenerator/CodeGenerator.cpp"
#include "library/scanner/Scanner.cpp"

void CompileFile(std::string filename)
{
    InputFile* file = new InputFile(filename);
    Scanner scanner = Scanner();
    OrderQueue* orders = scanner.ScanFile(file);

    delete file;

    CodeGenerator codeGenerator = CodeGenerator();

    AssemblyCode* assemblyCode = codeGenerator.GenerateOrders(*orders);

    delete orders;

    std::cout << assemblyCode->ToString() << "\n";
}

int main(int argc, char const* argv[])
{
    CompileFile(argv[1]);
    return 0;
}

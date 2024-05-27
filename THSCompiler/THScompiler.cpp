#include <iostream>

#include "library/scanner/Scanner.cpp"

#include "library/parser/parserDefinitions/GeneralParserDefinitions.cpp"
#include "library/parser/parserDefinitions/StatementParserDefinitions.cpp"
#include "library/parser/parserDefinitions/ExpressionParserDefinitions.cpp"
#include "library/parser/parserDefinitions/DeclarationParserDefinitions.cpp"

#include "library/codeGenerator/generator/CodeGenerator.hpp"
#include "library/codeGenerator/generator/DeclarationCodeGenerator.cpp"
#include "library/codeGenerator/generator/StatementCodeGenerator.cpp"

void CompileFile(std::string filename) {
    InputFile* file = new InputFile(filename);

    // Scanning
    TokenList* tokens = Scanner.Scan(file);
    delete file;

    // Parsing
    SyntaxTree* syntaxTree = PredictiveParser.Parse(tokens);
    delete tokens;
    std::cout << syntaxTree->ToString() << std::endl;

    // Code generation
    std::shared_ptr<AssemblyCode> assemblyCode = CodeGenerator.GenerateCode(syntaxTree);
    delete syntaxTree;

    std::cout << assemblyCode->ToString() << std::endl;
}

int main(int argc, char const *argv[])
{
    CompileFile(argv[1]);
    return 0;
}

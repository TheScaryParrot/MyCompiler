#include <iostream>

#include "library/codeGenerator/generator/CodeGenerator.cpp"
#include "library/parser/parserDefinitions/DeclarationParserDefinitions.cpp"
#include "library/parser/parserDefinitions/ExpressionParserDefinitions.cpp"
#include "library/parser/parserDefinitions/GeneralParserDefinitions.cpp"
#include "library/parser/parserDefinitions/StatementParserDefinitions.cpp"
#include "library/scanner/Scanner.cpp"

void CompileFile(std::string filename)
{
    InputFile* file = new InputFile(filename);

    // Scanning
    TokenList* tokens = Scanner.Scan(file);
    delete file;

    // Parsing
    SyntaxTree* syntaxTree = PredictiveParser.Parse(tokens);
    delete tokens;

    // Code generation
    CodeGenerator* codeGenerator = new CodeGenerator();
    AssemblyCode* assemblyCode = codeGenerator->GenerateCode(syntaxTree);
    delete syntaxTree;

    std::cout << "\n------Generated code------" << std::endl;
    std::cout << assemblyCode->ToString() << std::endl;

    delete assemblyCode;
}

int main(int argc, char const* argv[])
{
    CompileFile(argv[1]);
    return 0;
}

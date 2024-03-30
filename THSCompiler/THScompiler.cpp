#include <iostream>

#include "library/scanner/Scanner.cpp"

#include "library/parser/parserDefinitions/GeneralParserDefinitions.cpp"
#include "library/parser/parserDefinitions/StatementParserDefinitions.cpp"
#include "library/parser/parserDefinitions/ExpressionParserDefinitions.cpp"
#include "library/parser/parserDefinitions/DeclarationParserDefinitions.cpp"

void CompileFile(std::string filename) {
    InputFile* file = new InputFile(filename);

    // Scanning
    TokenList* tokens = Scanner.Scan(file);
    delete file;

    // Parsing
    SyntaxTree* syntaxTree = PredictiveParser.Parse(tokens);
    std::cout << syntaxTree->ToString() << std::endl;
    delete syntaxTree;

    delete tokens;
}

int main(int argc, char const *argv[])
{
    CompileFile(argv[1]);
    return 0;
}

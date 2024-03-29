#include <iostream>

#include "library/scanner/Scanner.cpp"
#include "library/parser/SyntaxTree.cpp"

#include "library/parser/grammarPatterns/start/expressions/ExpressionPattern.cpp"

void CompileFile(std::string filename) {
    InputFile* file = new InputFile(filename);
    TokenList* tokens = Scanner.Scan(file);
    delete file;
    
    SyntaxTree* syntaxTree = new SyntaxTree(tokens);
    std::cout << syntaxTree->ToString() << std::endl;
    delete syntaxTree;

    delete tokens;
}

int main(int argc, char const *argv[])
{
    CompileFile(argv[1]);
    return 0;
}

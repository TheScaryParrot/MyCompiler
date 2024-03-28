#include <iostream>

#include "library/scanner/Scanner.cpp"

void CompileFile(std::string filename) {
    InputFile* file = new InputFile(filename);
    TokenList* tokens = Scanner.Scan(file);
    delete file;
    std::cout << tokens->ToString() << std::endl;
    delete tokens;
}

int main(int argc, char const *argv[])
{
    CompileFile(argv[1]);
    return 0;
}

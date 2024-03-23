#pragma once

#include "../tokens/TokenList.cpp"

class SyntaxTree
{
public: 
    SyntaxTree();
    ~SyntaxTree();
    
    SyntaxTree* Parse(TokenList tokens);
    void Print();
};
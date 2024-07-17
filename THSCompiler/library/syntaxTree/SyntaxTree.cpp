#pragma once

#include <iostream>

#include "nodes/GlobalCodeNode.cpp"

class SyntaxTree
{
   private:
    GlobalCodeNode* code;

   public:
    SyntaxTree() { code = new GlobalCodeNode(); }
    ~SyntaxTree() { delete code; };

    void AddCodeLineNode(AbstractDeclarationNode* codeLine) { code->AddDeclaration(codeLine); }

    void SetCode(GlobalCodeNode* code) { this->code = code; }
    GlobalCodeNode* GetCode() { return code; };

    std::string ToString() { return "-----SyntaxTree-----\n" + code->ToString(); }
};
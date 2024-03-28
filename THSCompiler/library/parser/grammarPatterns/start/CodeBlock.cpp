#pragma once

#include "../IGrammarPattern.cpp"
#include "CodeLine.cpp"
#include <iostream>

class CodeBlock : public IGrammarPattern
{
public:
    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static CodeBlock* Parse(TokenList* tokens);

    void AddLine(CodeLine* line);

    virtual std::string ToString() override;

private:
    std::vector<CodeLine*> lines;
};

CodeBlock* CodeBlock::Parse(TokenList* tokens) {
    CodeBlock* codeBlock = new CodeBlock();

    while (tokens->HasNext()) {
        if (CodeLine::LookAhead(tokens) != ELookAheadCertainties::CertainlyPresent) {
            tokens->Next();
            continue;   
        }
        
        std::cout << "Parsing code line: " << tokens->Peek()->ToString() << std::endl;
        codeBlock->AddLine(CodeLine::Parse(tokens));
    }

    return codeBlock;
}

void CodeBlock::AddLine(CodeLine* line) {
    lines.push_back(line);
}

std::string CodeBlock::ToString() {
    std::string str = "{\n";
    for (CodeLine* line : lines) {
        str += line->ToString() + "\n";
    }
    str += "}\n";
    return str;
}
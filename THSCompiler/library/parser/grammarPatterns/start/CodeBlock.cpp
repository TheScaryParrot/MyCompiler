#pragma once

#include <library/parser/grammarPatterns/IGrammarPattern.cpp>
#include "CodeLine.cpp"
#include <iostream>

class CodeBlock : public IGrammarPattern
{
public:
    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static CodeBlock* Parse(TokenList* tokens);

    void AddLine(CodeLine* line);

private:
    std::vector<CodeLine*> lines;
};

CodeBlock* CodeBlock::Parse(TokenList* tokens) {
    CodeBlock* codeBlock = new CodeBlock();

    while (tokens->HasNext()) {
        if (CodeLine::LookAhead(tokens) != ELookAheadCertainties::CertainlyPresent) {
            break;   
        }
        
        codeBlock->AddLine(CodeLine::Parse(tokens));
    }

    return codeBlock;
}

void CodeBlock::AddLine(CodeLine* line) {
    lines.push_back(line);
}
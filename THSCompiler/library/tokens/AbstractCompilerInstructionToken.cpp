#pragma once

#include <string>

#include "Token.cpp"

class AbstractCompilerInstructionToken : public Token
{
   public:
    AbstractCompilerInstructionToken(std::string instruction) : Token("compilerInstruction") { this->instruction = instruction; }

    virtual bool IsThisToken(std::shared_ptr<Token> other) override
    {
        return this->Token::IsThisToken(other) &&
               this->IsThisInstruction(std::dynamic_pointer_cast<AbstractCompilerInstructionToken>(other)->instruction);
    }
    virtual std::string ToString() override { return Token::ToString() + ":" + this->instruction; }

    bool IsThisInstruction(std::string instruction) { return this->instruction == instruction; }

    virtual bool IsCompilerInstruction() override { return true; }

   private:
    std::string instruction;
};
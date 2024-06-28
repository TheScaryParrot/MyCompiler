#pragma once

#include <functional>
#include <vector>

#include "../utils/Queue.cpp"
#include "ICodeGenerator.cpp"

class Callable
{
   public:
    Callable(std::function<void(ICodeGenerator*)>);

    void SetFunction(std::function<void(ICodeGenerator*)> call);
    void Execute(ICodeGenerator* codeGenerator);

    void SetCodeStackProof(bool value);
    bool IsCodeStackProof();

    void SetCommentProof(bool value);
    bool IsCommentProof();

   private:
    std::function<void(ICodeGenerator*)> call;
    bool isCodeStackProof = false;
    bool isCommentProof = false;
};

Callable::Callable(std::function<void(ICodeGenerator*)> call) { this->call = call; }

void Callable::SetFunction(std::function<void(ICodeGenerator*)> call) { this->call = call; }
void Callable::Execute(ICodeGenerator* codeGenerator) { call(codeGenerator); }

void Callable::SetCodeStackProof(bool value) { isCodeStackProof = value; }
bool Callable::IsCodeStackProof() { return isCodeStackProof; }

void Callable::SetCommentProof(bool value) { isCommentProof = value; }
bool Callable::IsCommentProof() { return isCommentProof; }

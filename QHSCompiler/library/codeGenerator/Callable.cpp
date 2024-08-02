#pragma once

#include <functional>
#include <vector>

#include "../utils/Queue.cpp"
#include "ICodeGenerator.cpp"

class Callable
{
   public:
    Callable(std::function<void(ICodeGenerator*)>) { SetFunction(call); }

    void SetFunction(std::function<void(ICodeGenerator*)> call) { this->call = call; }
    void Execute(ICodeGenerator* codeGenerator) { call(codeGenerator); }

    void SetCodeStackProof(bool value) { isCodeStackProof = value; }
    bool IsCodeStackProof() { return isCodeStackProof; }

    void SetCommentProof(bool value) { isCommentProof = value; }
    bool IsCommentProof() { return isCommentProof; }

   private:
    std::function<void(ICodeGenerator*)> call;
    bool isCodeStackProof = false;
    bool isCommentProof = false;
};

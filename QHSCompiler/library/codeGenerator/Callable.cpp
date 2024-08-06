#pragma once

#include <functional>
#include <vector>

#include "../utils/Queue.cpp"
#include "CodeGenerator.cpp"
#include "ICallable.cpp"

class Callable : public ICallable
{
   public:
    Callable()
    {
        executeFunction = []() {};
        getFunction = [this]() { return this; };
    }

    virtual void SetExecuteFunction(std::function<void()> executeFunction) override
    {
        this->executeFunction = executeFunction;
    }
    virtual void Execute() override { executeFunction(); }

    virtual void SetGetFunction(std::function<ICallable*()> getFunction) override { this->getFunction = getFunction; }
    virtual ICallable* Get() override { return getFunction(); }

    virtual void SetCodeStackProof(bool codeStackProof) override { isCodeStackProof = codeStackProof; }
    virtual bool IsCodeStackProof() override { return isCodeStackProof; }

    virtual void SetCommentProof(bool commentProof) override { isCommentProof = commentProof; }
    virtual bool IsCommentProof() override { return isCommentProof; }

   private:
    std::function<void()> executeFunction;
    std::function<ICallable*()> getFunction;

    bool isCodeStackProof = false;
    bool isCommentProof = false;
};

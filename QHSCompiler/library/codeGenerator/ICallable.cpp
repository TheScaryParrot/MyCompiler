#pragma once

#include <functional>

class ICallable
{
   public:
    virtual void Execute() = 0;
    virtual void SetExecuteFunction(std::function<void()> executeFunction) = 0;

    virtual ICallable* Get() = 0;
    virtual void SetGetFunction(std::function<ICallable*()> getFunction) = 0;

    virtual bool IsCodeStackProof() = 0;
    virtual void SetCodeStackProof(bool codeStackProof) = 0;

    virtual bool IsCommentProof() = 0;
    virtual void SetCommentProof(bool commentProof) = 0;
};
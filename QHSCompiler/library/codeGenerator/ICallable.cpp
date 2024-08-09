#pragma once

#include <functional>

class ICallable
{
   public:
    virtual void Execute() = 0;
    virtual void SetExecuteFunction(std::function<void()> executeFunction) = 0;

    virtual void Encounter() = 0;
    virtual void SetEncounterFunction(std::function<void()> getFunction) = 0;

    virtual bool IsOrderQueueProof() = 0;
    virtual void SetOrderQueueProof(bool codeStackProof) = 0;

    virtual bool IsCommentProof() = 0;
    virtual void SetCommentProof(bool commentProof) = 0;
};
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
        encounterFunction = []() {};
    }

    virtual void SetExecuteFunction(std::function<void()> executeFunction) override
    {
        this->executeFunction = executeFunction;
    }
    virtual void Execute() override { executeFunction(); }

    virtual void SetEncounterFunction(std::function<void()> encounterFunction) override
    {
        this->encounterFunction = encounterFunction;
    }
    virtual void Encounter() override { return encounterFunction(); }

    virtual void SetOrderQueueProof(bool codeStackProof) override { isCodeStackProof = codeStackProof; }
    virtual bool IsOrderQueueProof() override { return isCodeStackProof; }

    virtual void SetCommentProof(bool commentProof) override { isCommentProof = commentProof; }
    virtual bool IsCommentProof() override { return isCommentProof; }

   private:
    std::function<void()> executeFunction;
    std::function<void()> encounterFunction;

    bool isCodeStackProof = false;
    bool isCommentProof = false;
};

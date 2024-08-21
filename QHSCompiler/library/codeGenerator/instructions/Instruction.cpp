#pragma once

#include <functional>

#include "../AbstractGenerator.cpp"
#include "../decode/CommentProofable.cpp"
#include "../decode/OrderQueueProofable.cpp"

class Instruction : public CommentProofable, public OrderQueueProofable
{
   private:
    std::function<void(AbstractGenerator*)> executeFunction;

   public:
    Instruction(std::function<void(AbstractGenerator*)> executeFunction, bool orderQueueProof, bool commentProof)
    {
        this->executeFunction = executeFunction;
        this->SetOrderQueueProof(orderQueueProof);
        this->SetCommentProof(commentProof);
    }

    void Execute(AbstractGenerator* generator) { this->executeFunction(generator); }
};
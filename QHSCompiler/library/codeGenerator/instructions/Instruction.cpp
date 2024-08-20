#pragma once

#include <functional>

#include "../AbstractGenerator.cpp"
#include "../decode/CommentProofable.cpp"
#include "../decode/OrderQueueProofable.cpp"

class Instruction : public CommentProofable, public OrderQueueProofable
{
   private:
    std::function<void(AbstractGenerator*, Order&)> fetchFunction;
    std::function<void(AbstractGenerator*)> executeFunction;

   public:
    Instruction(std::function<void(AbstractGenerator*, Order&)> fetchFunction,
                std::function<void(AbstractGenerator*)> executeFunction, bool orderQueueProof, bool commentProof)
    {
        this->fetchFunction = fetchFunction;
        this->executeFunction = executeFunction;
        this->SetOrderQueueProof(orderQueueProof);
        this->SetCommentProof(commentProof);
    }

    /// @brief Calls the instruction fetch function, allowing the instruction to alter current order and do stuff with
    /// the generator
    /// @param currentOrder Refrence to the current order. May be modified by the instruction
    void Fetch(AbstractGenerator* generator, Order& currentOrder) { this->fetchFunction(generator, currentOrder); }
    void Execute(AbstractGenerator* generator) { this->executeFunction(generator); }
};
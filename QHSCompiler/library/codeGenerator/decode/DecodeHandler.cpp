#pragma once

#include "../Order.cpp"
#include "../OrderQueue.cpp"
#include "../identifiers/IdentifierHandler.cpp"
#include "../instructions/InstructionHandler.cpp"

class DecodeHandler
{
   private:
    unsigned int orderQueueDepthCounter = 0;
    OrderQueue* queue;

    bool isInComment = false;

   public:
    DecodeHandler() { this->queue = new OrderQueue(); }
    ~DecodeHandler() { delete this->queue; }

    /// @brief Returns whether the order should be skipped
    bool Decode(Order order)
    {
        bool isCommentProof = false;
        bool isOrderQueueProof = false;

        if (order.GetType() == Order::Identifier)
        {
            Identifier* identifier = IdentifierHandler.GetIdentifier(order.GetName());

            if (identifier != nullptr)
            {
                isCommentProof = identifier->IsCommentProof();
                isOrderQueueProof = identifier->IsOrderQueueProof();
            }
        }
        else if (order.GetType() == Order::CompilerInstruction)
        {
            Instruction* instruction = InstructionHandler.GetInstruction(order.GetName());

            if (instruction != nullptr)
            {
                isCommentProof = instruction->IsCommentProof();
                isOrderQueueProof = instruction->IsOrderQueueProof();
            }
        }

        // Returns true when in comment (and not proof) or in order queue (and not proof)
        return !isCommentProof && this->isInComment || !isOrderQueueProof && this->orderQueueDepthCounter > 0;
    }

    void IncrementOrderQueueDepthCounter() { this->orderQueueDepthCounter++; }
    void DecrementOrderQueueDepthCounter() { this->orderQueueDepthCounter--; }

    void EnterComment() { this->isInComment = true; }
    void ExitComment() { this->isInComment = false; }
};
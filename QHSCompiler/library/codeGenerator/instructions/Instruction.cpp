#pragma once

#include <functional>

#include "../decode/CommentProofable.cpp"
#include "../decode/OrderQueueProofable.cpp"

class Instruction : public CommentProofable, public OrderQueueProofable
{
   private:
    std::function<void()> fetchFunction;
    std::function<void()> executeFunction;

   public:
    Instruction(std::function<void()> fetchFunction, std::function<void()> executeFunction)
    {
        this->fetchFunction = fetchFunction;
        this->executeFunction = executeFunction;
    }

    void Fetch() { this->fetchFunction(); }
    void Execute() { this->executeFunction(); }
};
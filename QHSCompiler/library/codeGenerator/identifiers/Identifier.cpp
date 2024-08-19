#pragma once

#include "../OrderQueue.cpp"
#include "../decode/CommentProofable.cpp"
#include "../decode/OrderQueueProofable.cpp"

class Identifier : public CommentProofable, public OrderQueueProofable
{
   private:
    OrderQueue* queue;

   public:
    Identifier(OrderQueue* queue) { this->queue = queue; }

    OrderQueue* GetQueue() { return this->queue; }
};
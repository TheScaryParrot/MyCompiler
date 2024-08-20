#pragma once

#include "../Order.cpp"

class IOrderFetcher
{
   public:
    virtual Order Next() = 0;
    virtual bool IsEmpty() = 0;
};
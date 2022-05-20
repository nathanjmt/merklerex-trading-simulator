#pragma once

#include "OrderBookEntry.h"

class OrderBookEntryComparator
{
    public:
        bool operator()(const OrderBookEntry& e1, const OrderBookEntry& e2) const
        {
            return e1.timestamp < e2.timestamp;
        }
};


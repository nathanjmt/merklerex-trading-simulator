#include "OrderBookEntry.h"
#include <string>
using std::string;

OrderBookEntry::OrderBookEntry(
        double _price, 
        double _amount, 
        string _timestamp, 
        string _product, 
        OrderBookType _orderType, 
        string _username
): price(_price),
    amount(_amount),
    timestamp(_timestamp),
    product(_product), 
    orderType(_orderType), 
    username(_username) { }

OrderBookType OrderBookEntry::stringToOrderBookType(string s)
{
    if (s == "ask") return OrderBookType::ask;
    if (s == "bid") return OrderBookType::bid;

    return OrderBookType::unknown;
}

bool OrderBookEntry::compareByTimestamp(OrderBookEntry& e1, OrderBookEntry& e2)
{
    return e1.timestamp < e2.timestamp;
}  

bool OrderBookEntry::compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2)
{
    return e1.price < e2.price;
}

bool OrderBookEntry::compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2)
{
    return e1.price > e2.price;
}


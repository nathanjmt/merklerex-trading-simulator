#pragma once

#include <string>

enum class OrderBookType { bid, ask, unknown, asksale, bidsale };

class OrderBookEntry
{
    public:
        /**
         * Creates an OrderBookEntry object.
         */
        OrderBookEntry(
                double _price, 
                double _amount, 
                std::string _timestamp, 
                std::string _product, 
                OrderBookType _orderType, 
                std::string username = "dataset"
        );

        /**
         * Returns an OrderBookType corresponding to the input string.
         */
        static OrderBookType stringToOrderBookType(std::string s);

        /**
         * Returns true if e1 has a timestamp before e2, false otherwise.
         */
        static bool compareByTimestamp(OrderBookEntry& e1, OrderBookEntry& e2);

        /**
         * Returns true if e1 has a price less than e2, false otherwise.
         */
        static bool compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2);

        /**
         * Returns true if e1 has a price more than e2, false otherwise.
         */
        static bool compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2);

        double price;
        double amount;
        std::string timestamp;
        std::string product;
        OrderBookType orderType;
        std::string username;
};


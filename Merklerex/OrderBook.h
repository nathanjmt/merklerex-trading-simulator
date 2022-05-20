#pragma once
#include "OrderBookEntry.h"
#include "OrderBookEntryComparator.h"
#include "CSVReader.h"
#include <set>
#include <string>
#include <vector>

class OrderBook
{
    public:
        /**
         * Constructs an OrderBook object from a csv data file.
         */
        OrderBook(std::string filename);

        /**
         * Returns vector of all know products in the dataset.
         */
        std::vector<std::string> getKnownProducts();

        /**
         * Returns vector of Orders according to the sent filters.
         */
        std::vector<OrderBookEntry> getOrders(
                OrderBookType type,
                std::string product,
                std::string timestamp
        );

        /**
         * Returns the earliest time in the orderbook.
         */
        std::string getEarliestTime();

        /** 
         * Returns the next time after the 
         * sent time in the orderbook.
         * If there is no next timestamp, wraps around to the start.
         */
        std::string getNextTime(std::string timestamp);

        /**
         * Inserts order into orderbook.
         */
        void insertOrder(OrderBookEntry& order);

        std::vector<OrderBookEntry> matchAsksToBids(
                std::string product,
                std::string timestamp
        );

        /**
         * Returns the highest price in orderbook
         */
        static double getHighPrice(std::vector<OrderBookEntry>& orders);

        /**
         * Returns the lowest price in orderbook
         */
        static double getLowPrice(std::vector<OrderBookEntry>& orders);

    private:
        /**
         * Using a multiset keeps order book entries sorted, thus no 
         * need for sorting during insertion.
         */
        std::multiset<OrderBookEntry, OrderBookEntryComparator> orders;
};


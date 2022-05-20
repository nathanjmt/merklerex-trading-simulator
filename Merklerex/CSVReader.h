#pragma once

#include "OrderBookEntry.h"
#include "OrderBookEntryComparator.h"
#include <set>
#include <string>
#include <vector>

class CSVReader
{
    public:
        /**
         * Creates a CSVReader object.
         */
        CSVReader();

        /**
         * Parses a CSV file to a vector of OrderBookEntry objects.
         */
        static std::multiset<OrderBookEntry, OrderBookEntryComparator>
            readCSV(std::string csvFile);

        /**
         * Separates a line based on separator into tokens.
         */
        static std::vector<std::string> tokenise(
                std::string csvLine,
                char separator
        );

        /**
         * Parses string to OrderBookEntry object.
         */
        static OrderBookEntry stringsToOBE(
                std::string price, 
                std::string amount, 
                std::string timestamp, 
                std::string product, 
                OrderBookType OrderBookType
        );

    private:
        static OrderBookEntry stringsToOBE(std::vector<std::string> strings);
};


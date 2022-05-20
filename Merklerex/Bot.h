#pragma once

#include "Logger.h"
#include "OrderBook.h"
#include "OrderBookEntry.h"
#include "PredictionBrain.h"
#include "Wallet.h"
#include <string>
#include <vector>

class Bot
{
    public:
        /**
         * Default bot constructor which uses 20200317.csv.
         */
        Bot();

        /** 
         * Bot constructor that uses given file name.
         */
        Bot(std::string csvFilename);

        /**
         * Initialises the program.
         */
        void init();

    private:
        OrderBook orderBook;
        Wallet wallet;
        Logger logger;
        std::vector<PredictionBrain> brains;
        std::string timestamp;

        void processTimeframe();
        bool enterBid(std::string productName, std::string currencyName);
        bool enterAsk(std::string productName, std::string currencyName);
        void processSale(OrderBookEntry& sale);
};


#pragma once

#include "OrderBook.h"
#include "Wallet.h"
#include <string>

class MerkelMain
{
    public:
        /**
         * Creates a MerkelMain object.
         */
        MerkelMain();

        /**
         * Call this to start the sim
         */
        void init();

    private: 
        std::string currentTime;
        OrderBook orderBook{"20200317.csv"};
        Wallet wallet;

        void printMenu();
        void printHelp();
        void printMarketStats();
        void enterAsk();
        void enterBid();
        void printWallet();
        void gotoNextTimeframe();
        int getUserOption();
        void processUserOption(int userOption);
};


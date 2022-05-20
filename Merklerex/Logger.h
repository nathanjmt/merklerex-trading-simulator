#pragma once

#include "OrderBookEntry.h"
#include "Wallet.h"
#include <fstream>
#include <string>
#include <vector>

class Logger
{
    public:
        /**
         * Default constructor for Logger, initializing ofstream for ask.txt,
         * bid.txt, sales.txt and assets.txt.
         */
        Logger();

        /**
         * Destructor for Logger, closes ofstream for the ofstreams.
         */
        ~Logger();

        /** 
         * Records bids, asks, sales and assets in a given timeframe.
         */
        void recordTimeframe(std::string timestamp, Wallet wallet);

        /**
         * Stores sale entry into Logger to be recorded.
         */
        void insertSale(OrderBookEntry& sale);

        /** 
         * Stores bid entry into logger to be recorded
         */
        void insertBid(OrderBookEntry& bid);

        /** 
         * Stores ask entry into logger to be recorded
         */
        void insertAsk(OrderBookEntry& ask);

    private:
        std::ofstream assetRecord;
        std::ofstream bidRecord;
        std::ofstream askRecord;
        std::ofstream salesRecord;
        std::vector<OrderBookEntry> bids;
        std::vector<OrderBookEntry> asks;
        std::vector<OrderBookEntry> sales;

        void recordBlankLine();
        void recordTimeframeHeader(std::string timestamp);
        void recordBids();
        void recordAsks();
        void recordSales();
        void recordBorder();
        void recordWalletState(Wallet wallet);
};


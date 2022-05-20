#pragma once

#include "CurrencyPair.h"
#include "OrderBook.h"
#include <string>

class PredictionBrain
{
    public:
        /**
         * Creates a PredictionBrain object with the corresponding CurrencyPair.
         */
        PredictionBrain(CurrencyPair _pair);

        /**
         * Updates the exponential moving average with the orders from the next
         * timeframe.
         */
        void getNextTimeframe(OrderBook& orderBook);
        int getNumberOfObservations();
        bool shouldBuy();
        bool shouldSell();
        std::string getProductName();
        std::string getAskCurrency();
        std::string getBidCurrency();

    private:
        CurrencyPair pair;
        double ema;
        int numberOfObservations, increaseStreak, decreaseStreak;
        std::string timestamp;

        double getMultiplier();
        void updateEma(double closingPrice);
};


#pragma once

#include "OrderBookEntry.h"
#include <iostream>
#include <map>
#include <string>

class Wallet 
{
    friend std::ostream& operator<<(std::ostream& os, Wallet& wallet);

    public:
        /**
         * Creates a Wallet object.
         */
        Wallet();

        /**
         * Insert currency to the wallet
         */
        void insertCurrency(std::string type, double amount);

        /**
         * Remove currency from the wallet
         */
        bool removeCurrency(std::string type, double amount);

        /**
         * Check if the wallet contains this much currency or more
         */
        bool containsCurrency(std::string type, double amount);

        /** 
         * Checks if the wallet can cope with this ask or bid.
         */
        bool canFulfillOrder(OrderBookEntry order);

        /** 
         * Updates the contents of the wallet
         * assumes the order was made by the owner of the wallet.
        */
        void processSale(OrderBookEntry& sale);

        /**
         * Generate a string representation of the wallet
         */
        std::string toString();

        /**
         * Returns the amount of the currency in the wallet.
         */
        double getAmount(std::string currency);

    private:
        std::map<std::string, double> currencies;
};


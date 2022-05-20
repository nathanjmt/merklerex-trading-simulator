#include "CurrencyPair.h"
#include "OrderBook.h"
#include "OrderBookEntry.h"
#include "PredictionBrain.h"
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;

PredictionBrain::PredictionBrain(CurrencyPair _pair):
    pair(_pair),
    ema(0),
    numberOfObservations(0),
    increaseStreak(0),
    decreaseStreak(0),
    timestamp("") { }

void PredictionBrain::getNextTimeframe(OrderBook& orderBook)
{
    if (timestamp.size() == 0) timestamp = orderBook.getEarliestTime();
    else timestamp = orderBook.getNextTime(timestamp);

    vector<OrderBookEntry> orders
        = orderBook.getOrders(OrderBookType::ask, productMap[pair], timestamp);

    if (orders.size() == 0) return;

    double closingPrice = orderBook.getHighPrice(orders);

    updateEma(closingPrice);

    numberOfObservations++;
}

int PredictionBrain::getNumberOfObservations()
{
    return numberOfObservations;
}

void PredictionBrain::updateEma(double closingPrice)
{
    if (ema == 0) ema = closingPrice;
    else {
        double newEma = closingPrice * getMultiplier()
            + ema * (1 - getMultiplier());

        if (newEma > ema) {
            increaseStreak++;
            decreaseStreak = 0;
        }

        if (newEma < ema) {
            decreaseStreak++;
            increaseStreak = 0;
        }

        ema = newEma;
    }
}

bool PredictionBrain::shouldBuy()
{
    return increaseStreak >= 3;
}

bool PredictionBrain::shouldSell()
{
    return decreaseStreak >= 2;
}

string PredictionBrain::getProductName()
{
    return productMap[pair];
}

string PredictionBrain::getAskCurrency()
{
    return askMap[pair];
}

string PredictionBrain::getBidCurrency()
{
    return bidMap[pair];
}

double PredictionBrain::getMultiplier()
{
    double observationPeriod = 20;

    return 2.0 / (observationPeriod + 1);
}


#include "Bot.h"
#include "CurrencyPair.h"
#include "MerkelMain.h"
#include "OrderBook.h"
#include "PredictionBrain.h"
#include <iostream>
#include <iomanip>
#include <string>
using std::cout;
using std::endl;

int main()
{
    Bot bot("20200601.csv");
    // Bot bot;
    // Bot bot("test.csv");

    bot.init();
}


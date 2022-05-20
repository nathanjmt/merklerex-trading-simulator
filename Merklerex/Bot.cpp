#include "Bot.h"
#include "CSVReader.h"
#include "CurrencyPair.h"
#include "OrderBook.h"
#include "OrderBookEntry.h"
#include "PredictionBrain.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::cin;
using std::endl;
using std::find;
using std::string;
using std::vector;

double getPriceToBid(vector<OrderBookEntry>& asks)
{
    double high = OrderBook::getHighPrice(asks),
           low = OrderBook::getLowPrice(asks);

    return low + (high - low) * 0.25; // 25th percentile of bids
}

double getPriceToAsk(vector<OrderBookEntry>& bids)
{
    double high = OrderBook::getHighPrice(bids),
           low = OrderBook::getLowPrice(bids);

    return low + (high - low) * 0.75; // 75th percentile of asks we want top end 
}

bool isValidCurrency(string input)
{
    static vector<string> validCurrencies = { "BTC", "ETH", "DOGE", "USDT" };

    return find(validCurrencies.begin(), validCurrencies.end(), input)
        != validCurrencies.end();
}

Bot::Bot(): orderBook("20200317.csv"),
    timestamp(""),
    brains({
        PredictionBrain(CurrencyPair::btc_usdt),
        PredictionBrain(CurrencyPair::doge_btc),
        PredictionBrain(CurrencyPair::doge_usdt),
        PredictionBrain(CurrencyPair::eth_btc),
        PredictionBrain(CurrencyPair::eth_usdt)
    }) { }

Bot::Bot(string csvFilename): orderBook(csvFilename),
    timestamp(""),
    brains({
        PredictionBrain(CurrencyPair::btc_usdt),
        PredictionBrain(CurrencyPair::doge_btc),
        PredictionBrain(CurrencyPair::doge_usdt),
        PredictionBrain(CurrencyPair::eth_btc),
        PredictionBrain(CurrencyPair::eth_usdt)
    }) { }


void Bot::init()
{
    string currency, amountInput;
    double amount;
    int observations = 0;

    timestamp = orderBook.getEarliestTime();

    do {
        cout << "Please enter currency (eg. BTC, ETH, DOGE): ";
        cin >> currency;
    } while (!isValidCurrency(currency));

    do {
        cout << "Please enter amount: ";
        cin >> amountInput;

        amount = std::stod(amountInput);
    } while (amount < 0);

    wallet.insertCurrency(currency, amount);
    logger.recordTimeframe("Initial", wallet);

    do processTimeframe();
    while (timestamp != orderBook.getEarliestTime());
}

void Bot::processTimeframe()
{
    cout << timestamp << endl;

    vector<OrderBookEntry> sales;

    for (PredictionBrain& brain : brains) {
        bool enteredOrder = false;

        brain.getNextTimeframe(orderBook);

        // Collect data for initial 20 timeframes for predictions
        if (brain.getNumberOfObservations() < 20) continue;
        if (brain.shouldBuy())
            enteredOrder
                = enterBid(brain.getProductName(), brain.getBidCurrency());
        if (brain.shouldSell())
            enteredOrder
                = enterAsk(brain.getProductName(), brain.getAskCurrency());
        if (!enteredOrder) continue;

        cout << brain.getProductName() << endl;

        vector<OrderBookEntry> newSales
            = orderBook.matchAsksToBids(brain.getProductName(), timestamp);

        sales.insert(sales.end(), newSales.begin(), newSales.end());
    }

    for (OrderBookEntry& sale : sales) {
        if (sale.username != "simuser") continue;

        processSale(sale);
    }

    cout << endl << wallet << endl;

    logger.recordTimeframe(timestamp, wallet);
    timestamp = orderBook.getNextTime(timestamp);
}

bool Bot::enterBid(string productName, string currencyName)
{
    vector<OrderBookEntry> asks = orderBook.getOrders(
            OrderBookType::ask,
            productName,
            timestamp
    );

    if (asks.size() == 0) return false;

    double price = getPriceToBid(asks),
           amount = wallet.getAmount(currencyName);

    if (amount == 0) return false;

    OrderBookEntry bid(
        price,
        amount,
        timestamp,
        productName,
        OrderBookType::bid,
        "simuser"
    );

    logger.insertBid(bid);
    orderBook.insertOrder(bid);

    return true;
}

bool Bot::enterAsk(string productName, string currencyName)
{
    vector<OrderBookEntry> bids = orderBook.getOrders(
            OrderBookType::bid,
            productName,
            timestamp
    );

    if (bids.size() == 0) return false;

    double price = getPriceToAsk(bids),
           amount = wallet.getAmount(currencyName);

    if (amount == 0) return false;

    OrderBookEntry ask(
        price,
        amount,
        timestamp,
        productName,
        OrderBookType::ask,
        "simuser"
    );

    logger.insertAsk(ask);
    orderBook.insertOrder(ask);

    return true;
}

void Bot::processSale(OrderBookEntry& sale)
{
    if (sale.orderType != OrderBookType::asksale
            && sale.orderType != OrderBookType::bidsale) return;

    vector<string> currencies = CSVReader::tokenise(sale.product, '/');
    double outgoingAmount = sale.orderType == OrderBookType::asksale
        ? sale.amount
        : sale.amount * sale.price;
    string outgoingCurrency = sale.orderType == OrderBookType::asksale
        ? currencies[0]
        : currencies[1];

    if (!wallet.containsCurrency(outgoingCurrency, outgoingAmount)) return;

    logger.insertSale(sale);
    wallet.processSale(sale);
}


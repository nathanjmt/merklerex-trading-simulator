#include "Logger.h"
#include "OrderBookEntry.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
using std::cout;
using std::endl;
using std::function;
using std::max;
using std::ofstream;
using std::string;
using std::to_string;

Logger::Logger(): assetRecord("assets.txt"),
    bidRecord("bid.txt"),
    salesRecord("sales.txt"),
    askRecord("ask.txt") { }

Logger::~Logger()
{
    assetRecord.close();
    bidRecord.close();
    askRecord.close();
    salesRecord.close();
}

void Logger::recordBlankLine()
{
    assetRecord << endl;
    bidRecord << endl;
    askRecord << endl;
    salesRecord << endl;
}

void Logger::recordBorder()
{
    static string border = "==================================================";

    assetRecord << border << endl;
    bidRecord << border << endl;
    askRecord << border << endl;
    salesRecord << border << endl;
}

void Logger::recordTimeframeHeader(string timestamp)
{
    recordBlankLine();
    recordBorder();

    assetRecord << timestamp << endl;
    bidRecord << timestamp << endl;
    askRecord << timestamp << endl;
    salesRecord << timestamp << endl;
}

void Logger::recordWalletState(Wallet wallet)
{
    assetRecord << wallet << endl;
}

void Logger::insertSale(OrderBookEntry& sale)
{
    sales.push_back(sale);
}

void Logger::insertBid(OrderBookEntry& bid)
{
    bids.push_back(bid);
}

void Logger::insertAsk(OrderBookEntry& ask)
{
    asks.push_back(ask);
}

void Logger::recordTimeframe(string timestamp, Wallet wallet)
{
    recordTimeframeHeader(timestamp);
    recordBids();
    recordAsks();
    recordSales();
    recordWalletState(wallet);
}

void Logger::recordBids()
{
    string headers[] = { "Product", "Price", "Amount" };
    string::size_type nameLen = headers[0].size(),
        priceLen = headers[1].size(),
        amountLen = headers[2].size();

    for (const OrderBookEntry& bid : bids) {
        nameLen = max(nameLen, bid.product.size());
        priceLen = max(priceLen, to_string(bid.price).size());
        amountLen = max(amountLen, to_string(bid.amount).size());
    }

    string spaceForName(nameLen - headers[0].size() + 1, ' '),
           spaceForPrice(priceLen - headers[1].size() + 1, ' '),
           spaceForAmount(amountLen - headers[2].size() + 1, ' ');

    bidRecord << "| " << headers[0] << spaceForName
        << '|' << spaceForPrice << headers[1]
        << " |" << spaceForAmount << headers[2]
        << " |" << endl;

    for (const OrderBookEntry& bid : bids) {
        spaceForName = string(nameLen - bid.product.size() + 1, ' ');
        spaceForPrice = string(priceLen - to_string(bid.price).size() + 1, ' '),
        spaceForAmount
            = string(amountLen - to_string(bid.amount).size() + 1, ' ');

        bidRecord << "| " << bid.product << spaceForName
            << '|' << spaceForPrice << to_string(bid.price)
            << " |" << spaceForAmount << to_string(bid.amount)
            << " |" << endl;
    }

    bids.clear();
}

void Logger::recordAsks()
{
    string headers[] = { "Product", "Price", "Amount" };
    string::size_type nameLen = headers[0].size(),
        priceLen = headers[1].size(),
        amountLen = headers[2].size();

    for (const OrderBookEntry& ask : asks) {
        nameLen = max(nameLen, ask.product.size());
        priceLen = max(priceLen, to_string(ask.price).size());
        amountLen = max(amountLen, to_string(ask.amount).size());
    }

    string spaceForName(nameLen - headers[0].size() + 1, ' '),
           spaceForPrice(priceLen - headers[1].size() + 1, ' '),
           spaceForAmount(amountLen - headers[2].size() + 1, ' ');

    askRecord << "| " << headers[0] << spaceForName
        << '|' << spaceForPrice << headers[1]
        << " |" << spaceForAmount << headers[2]
        << " |" << endl;

    for (const OrderBookEntry& ask : asks) {
        spaceForName = string(nameLen - ask.product.size() + 1, ' ');
        spaceForPrice = string(priceLen - to_string(ask.price).size() + 1, ' ');
        spaceForAmount
            = string(amountLen - to_string(ask.amount).size() + 1, ' ');

        askRecord << "| " << ask.product << spaceForName
            << '|' << spaceForPrice << to_string(ask.price)
            << " |" << spaceForAmount << to_string(ask.amount)
            << " |" << endl;
    }

    asks.clear();
}

void Logger::recordSales()
{
    string headers[] = { "Type", "Product", "Price", "Amount" };
    string::size_type typeLen = headers[0].size(),
            nameLen = headers[1].size(),
            priceLen = headers[2].size(),
            amountLen = headers[3].size();

    for (const OrderBookEntry& sale : sales) {
        nameLen = max(nameLen, sale.product.size());
        priceLen = max(priceLen, to_string(sale.price).size());
        amountLen = max(amountLen, to_string(sale.amount).size());
    }

    string spaceForType = " ",
           spaceForName(nameLen - headers[1].size() + 1, ' '),
           spaceForPrice(priceLen - headers[2].size() + 1, ' '),
           spaceForAmount(amountLen - headers[3].size() + 1, ' ');

    salesRecord << "| " << headers[0] << spaceForType
        << "| " << headers[1] << spaceForName
        << '|' << spaceForPrice << headers[2]
        << " |" << spaceForAmount << headers[3]
        << " |" << endl;

    spaceForType = "  ";

    for (const OrderBookEntry& sale : sales) {
        string type = sale.orderType == OrderBookType::asksale ? "Ask" : "Bid";
        spaceForName = string(nameLen - sale.product.size() + 1, ' ');
        spaceForPrice
            = string(priceLen - to_string(sale.price).size() + 1, ' ');
        spaceForAmount
            = string(amountLen - to_string(sale.amount).size() + 1, ' ');

        salesRecord << "| " << type << spaceForType
            << "| " << sale.product << spaceForName
            << '|' << spaceForPrice << to_string(sale.price)
            << " |" << spaceForAmount << to_string(sale.amount)
            << " |" << endl;
    }

    sales.clear();
}


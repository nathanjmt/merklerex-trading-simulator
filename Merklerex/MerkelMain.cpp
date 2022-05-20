#include "CSVReader.h"
#include "MerkelMain.h"
#include "OrderBookEntry.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::exception;
using std::getline;
using std::stoi;
using std::string;
using std::vector;

MerkelMain::MerkelMain() { }

void MerkelMain::init()
{
    int input;
    currentTime = orderBook.getEarliestTime();

    wallet.insertCurrency("BTC", 10);

    while (true) {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

void MerkelMain::printMenu()
{
    // 1 print help
    cout << "1: Print help " << endl
    // 2 print exchange stats
        << "2: Print exchange stats" << endl
    // 3 make an offer
        << "3: Make an offer " << endl
    // 4 make a bid 
        << "4: Make a bid " << endl
    // 5 print wallet
        << "5: Print wallet " << endl
    // 6 continue   
        << "6: Continue " << endl
        << "============== " << endl
        << "Current time is: " << currentTime << endl;
}

void MerkelMain::printHelp()
{
    cout << "Help - your aim is to make money. Analyse the market and make bids"
            " and offers. " << endl;
}

void MerkelMain::printMarketStats()
{
    for (const string& p : orderBook.getKnownProducts()) {
        vector<OrderBookEntry> entries
                = orderBook.getOrders(OrderBookType::ask, p, currentTime);
        cout << "Product: " << p << endl;
        cout << "Asks seen: " << entries.size() << endl;
        cout << "Max ask: " << OrderBook::getHighPrice(entries) << endl;
        cout << "Min ask: " << OrderBook::getLowPrice(entries) << endl;
    }

    // cout << "OrderBook contains :  " << orders.size() << " entries" << endl;
    // unsigned int bids = 0;
    // unsigned int asks = 0;
    // for (OrderBookEntry& e : orders)
    // {
    //     if (e.orderType == OrderBookType::ask)
    //     {
    //         asks ++;
    //     }
    //     if (e.orderType == OrderBookType::bid)
    //     {
    //         bids ++;
    //     }  
    // }    
    // cout << "OrderBook asks:  " << asks << " bids:" << bids << endl;
}

void MerkelMain::enterAsk()
{
    cout << "Make an ask - enter the amount: product,price,amount, "
            "eg  ETH/BTC,200,0.5" << endl;

    string input;
    getline(cin, input);

    vector<string> tokens = CSVReader::tokenise(input, ',');

    if (tokens.size() != 3) {
        cout << "MerkelMain::enterAsk Bad input! " << input << endl;
        return;
    }

    try {
        OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2], 
                currentTime, 
                tokens[0], 
                OrderBookType::ask 
        );
        obe.username = "simuser";

        if (wallet.canFulfillOrder(obe)) {
            cout << "Wallet looks good. " << endl;
            orderBook.insertOrder(obe);
        } else {
            cout << "Wallet has insufficient funds. " << endl;
        }

    } catch (const exception& e) {
        cout << " MerkelMain::enterAsk Bad input " << endl;
    }
}

void MerkelMain::enterBid()
{
    cout << "Make an bid - enter the amount: product,price,amount, "
            "eg  ETH/BTC,200,0.5" << endl;

    string input;
    getline(cin, input);

    vector<string> tokens = CSVReader::tokenise(input, ',');

    if (tokens.size() != 3) {
        cout << "MerkelMain::enterBid Bad input! " << input << endl;
        return;
    }

    try {
        OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2], 
                currentTime, 
                tokens[0], 
                OrderBookType::bid 
        );
        obe.username = "simuser";

        if (wallet.canFulfillOrder(obe)) {
            cout << "Wallet looks good. " << endl;
            orderBook.insertOrder(obe);
        } else {
            cout << "Wallet has insufficient funds. " << endl;
        }

    } catch (const exception& e) {
        cout << " MerkelMain::enterBid Bad input " << endl;
    }
}

void MerkelMain::printWallet()
{
    cout << wallet.toString() << endl;
}

void MerkelMain::gotoNextTimeframe()
{
    cout << "Going to next time frame. " << endl;

    for (string p : orderBook.getKnownProducts()) {
        vector<OrderBookEntry> sales
            = orderBook.matchAsksToBids(p, currentTime);

        cout << "matching " << p << endl;
        cout << "Sales: " << sales.size() << endl;

        for (OrderBookEntry& sale : sales) {
            cout << "Sale price: " << sale.price << " amount "
                << sale.amount << endl; 

            if (sale.username == "simuser") {
                // update the wallet
                wallet.processSale(sale);
            }
        }
    }

    currentTime = orderBook.getNextTime(currentTime);
}
 
int MerkelMain::getUserOption()
{
    int userOption = 0;
    string line;

    cout << "Type in 1-6" << endl;
    getline(cin, line);

    try {
        userOption = stoi(line);
    } catch (const exception& e) {
        // 
    }

    cout << "You chose: " << userOption << endl;

    return userOption;
}

void MerkelMain::processUserOption(int userOption)
{
    switch (userOption) {
        case 1:
            printHelp();
            break;
        case 2:
            printMarketStats();
            break;
        case 3:
            enterAsk();
            break;
        case 4:
            enterBid();
            break;
        case 5:
            printWallet();
            break;
        case 6:
            gotoNextTimeframe();
            break;
        default:
            cout << "Invalid choice. Choose 1-6" << endl;
            break;
    }
}


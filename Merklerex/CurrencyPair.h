#pragma once

#include <string>
#include <unordered_map>

enum class CurrencyPair
{
    btc_usdt,
    doge_btc,
    doge_usdt,
    eth_btc,
    eth_usdt
};

static std::unordered_map<CurrencyPair, std::string> productMap = {
    { CurrencyPair::btc_usdt, "BTC/USDT" },
    { CurrencyPair::doge_btc, "DOGE/BTC" },
    { CurrencyPair::doge_usdt, "DOGE/USDT" },
    { CurrencyPair::eth_btc, "ETH/BTC" },
    { CurrencyPair::eth_usdt, "ETH/USDT" }
};

static std::unordered_map<CurrencyPair, std::string> askMap = {
    { CurrencyPair::btc_usdt, "BTC" },
    { CurrencyPair::doge_btc, "DOGE" },
    { CurrencyPair::doge_usdt, "DOGE" },
    { CurrencyPair::eth_btc, "ETH" },
    { CurrencyPair::eth_usdt, "ETH" }
};

static std::unordered_map<CurrencyPair, std::string> bidMap = {
    { CurrencyPair::btc_usdt, "USDT" },
    { CurrencyPair::doge_btc, "BTC" },
    { CurrencyPair::doge_usdt, "USDT" },
    { CurrencyPair::eth_btc, "BTC" },
    { CurrencyPair::eth_usdt, "USDT" }
};


#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <utility>
#include <unordered_map>

// Define data structures
enum class OrderBookOrderType
{
    MARKET,
    LIMIT,
    CANCEL,
    MODIFY
};

enum class OrderBookOrderSide
{
    BUY,
    SELL
};

struct OrderBookOrder
{
    std::string orderId;
    std::string symbol;
    OrderBookOrderType type;
    OrderBookOrderSide side;
    double price;
    double quantity;
    uint64_t timestamp;
};

struct OrderBookEntry
{
    OrderBookEntry(double price, double quantity, OrderBookOrderSide side, int priority);
    double price;
    double quantity;
    OrderBookOrderSide side;
    int priority;
};

struct OrderBook
{
    std::vector<OrderBookEntry> bids;
    std::vector<OrderBookEntry> asks;
    double lastTradePrice = 0.0;
    uint64_t lastUpdateTime = 0;
};

struct OrderBookMarketDataUpdate
{
    std::string symbol;
    std::vector<OrderBookEntry> bids;
    std::vector<OrderBookEntry> asks;
    double lastTradePrice;
    uint64_t timestamp;
};

struct MarketImpact
{
    uint64_t timestamp;
    double quantity;
    double fillRatio;
    OrderBookOrderSide side;
};

class OrderBookProcessor
{
public:
    OrderBookProcessor();
    ~OrderBookProcessor();

    // Reset all metrics and clear order book state
    void resetMetrics();

    // Order processing methods
    void processOrder(const OrderBookOrder &order);
    void processMarketDataUpdate(const OrderBookMarketDataUpdate &update);

    // Market microstructure metrics
    double getSpread(const std::string &symbol) const;
    double getAverageSpread(const std::string &symbol, int lookbackPeriod) const;
    double getVolumeImbalance(const std::string &symbol) const;
    double getMidPrice(const std::string &symbol) const;
    double getMicroPrice(const std::string &symbol) const;

    // Market impact analysis
    double getHistoricalVol(const std::string &symbol, int lookbackPeriod) const;
    std::pair<double, double> calculateMarketImpact(const std::string &symbol, double quantity, OrderBookOrderSide side);
    std::unordered_map<std::string, double> analyzeOrderFlowToxicity(const std::string &symbol, int lookbackPeriod = 100) const;
    std::pair<double, double> calculateEffectiveSpread(const std::string &symbol, int lookbackPeriod = 100) const;

    // Helper methods
    std::string getOrderBookSnapshot(const std::string &symbol, int depth) const;

private:
    // Data members
    std::map<std::string, OrderBook> orderBooks_;
    std::map<std::string, std::vector<OrderBookMarketDataUpdate>> historicalData_;
    std::map<std::string, std::vector<OrderBookMarketDataUpdate>> marketDataHistory_;
    std::map<std::string, OrderBookOrder> activeOrders_;
    std::map<std::string, std::vector<MarketImpact>> marketImpactHistory_;

    // Additional history for metrics
    std::map<std::string, std::vector<std::pair<uint64_t, double>>> spreadHistory_;
    std::map<std::string, std::vector<std::pair<uint64_t, double>>> depthHistory_;
    std::map<std::string, std::vector<std::pair<uint64_t, double>>> volumeImbalanceHistory_;
    std::map<std::string, std::vector<std::pair<uint64_t, double>>> priceImpactHistory_;
    std::map<std::string, std::vector<std::pair<uint64_t, double>>> midPriceHistory_;
    std::map<std::string, std::vector<std::pair<uint64_t, double>>> microPriceHistory_;
    std::map<std::string, std::vector<MarketImpact>> marketImpactMetrics_;

    // Private helper methods
    void updateOrderBook(const OrderBookMarketDataUpdate &update);
    void processLimitOrder(const OrderBookOrder &order);
    void processMarketOrder(const OrderBookOrder &order);
    void processCancelOrder(const OrderBookOrder &order);
    void processModifyOrder(const OrderBookOrder &order);
    void updateMarketMetrics(const std::string &symbol);
    double calculatePriceImpact(const std::string &symbol, double quantity, OrderBookOrderSide side);
};

// Factory function to create an OrderBookProcessor instance
std::unique_ptr<OrderBookProcessor> createOrderBookProcessor();
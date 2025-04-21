#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include "order_book_processor.h"
#include <map>
#include <unordered_set>

// Forward declarations
struct MarketDataUpdate;
struct Order;
class OrderBook;

/**
 * @brief Class representing a trading strategy that uses algorithms from previous weeks
 *
 * Students should implement this class to fulfill the requirements of Part 3:
 * - Use dynamic programming for optimal order sizing
 * - Apply graph algorithms for analyzing market relationships
 * - Implement efficient sorting algorithms for processing market data
 */
class TradingStrategy
{
public:
    TradingStrategy();
    ~TradingStrategy();

    /**
     * @brief Initialize the strategy with configuration parameters
     * @param params Configuration parameters for the strategy
     * @return true if initialization successful, false otherwise
     */
    virtual bool initialize(const std::unordered_map<std::string, std::string> &params) = 0;

    /**
     * @brief Process a new market data update and generate trading signals
     * @param marketData The latest market data update
     * @return Vector of orders to be executed (if any)
     */
    virtual std::vector<Order> onMarketDataUpdate(const MarketDataUpdate &marketData) = 0;

    /**
     * @brief Calculate optimal order size using dynamic programming
     *
     * Implement a dynamic programming algorithm to determine the optimal
     * order size based on current market conditions, risk parameters,
     * and execution costs.
     *
     * @param price Current price of the asset
     * @param volatility Recent volatility measure
     * @param maxRisk Maximum risk allowed per trade
     * @return The optimal order size
     */
    virtual int calculateOptimalOrderSize(double price, double volatility, double maxRisk) = 0;

    /**
     * @brief Analyze market relationships using graph algorithms
     *
     * Implement a graph-based algorithm to analyze relationships between
     * different securities in the market. This can include:
     * - Correlation analysis
     * - Lead-lag relationships
     * - Market structure visualization
     *
     * @param marketData Recent market data for multiple securities
     * @return Adjacency matrix or other representation of market relationships
     */
    virtual std::vector<std::vector<double>> analyzeMarketRelationships(
        const std::vector<MarketDataUpdate> &marketData) = 0;

    /**
     * @brief Process market data efficiently using appropriate sorting algorithms
     *
     * Implement efficient sorting and filtering to process large amounts of
     * market data for signal generation.
     *
     * @param marketData Vector of market data updates to process
     * @return Processed and sorted data
     */
    virtual std::vector<MarketDataUpdate> processMarketData(
        const std::vector<MarketDataUpdate> &marketData) = 0;

    /**
     * @brief Get the name of this strategy
     * @return Strategy name
     */
    std::string getName() const { return name_; }

    // Order generation
    virtual Order generateOrder(const MarketDataUpdate &update) = 0;
    std::vector<Order> generateOrders(const MarketDataUpdate &update);

    // Market analysis
    void updateMarketConditions(const MarketDataUpdate &update);
    virtual double calculateOptimalSize(const std::string &symbol) const = 0;
    virtual double calculateSpread(const std::string &symbol) const = 0;

    // Strategy parameters
    void updateParameters(const std::string &symbol, const std::map<std::string, double> &params);
    std::map<std::string, double> getParameters(const std::string &symbol) const;

protected:
    std::string name_;
    bool isActive_ = false;

    // Parameters for the strategy
    double riskLimit_ = 0.0;
    double positionLimit_ = 0.0;
    int lookbackPeriod_ = 0;

    // Market state
    struct MarketState
    {
        double midPrice;
        double spread;
        double volume;
        double volatility;
        uint64_t lastUpdateTime;
    };

    std::map<std::string, MarketState> marketStates_;
    std::map<std::string, std::map<std::string, double>> strategyParameters_;

    // Strategy parameters
    double minSpread_ = 0.01;     // Minimum spread to trade
    double maxPosition_ = 1000.0; // Maximum position size
    double riskPerTrade_ = 0.01;  // Risk per trade (1% of capital)
    double targetProfit_ = 0.02;
    TradingStrategy(const std::string &name);
    // Target profit per trade (2%)
};

/**
 * @brief Factory function to create a concrete trading strategy
 * @param strategyType Type of strategy to create
 * @param name Name for the strategy instance
 * @return Shared pointer to the created strategy
 */
std::shared_ptr<TradingStrategy> createStrategy(const std::string &strategyType, const std::string &name);
class MeanReversionStrategy : public TradingStrategy
{
public:
    MeanReversionStrategy(const std::string &name);
    Order generateOrder(const MarketDataUpdate &update) override;
    double calculateSpread(const std::string &symbol) const override;
    bool initialize(const std::unordered_map<std::string, std::string> &params) override;
    std::vector<Order> onMarketDataUpdate(const MarketDataUpdate &marketData) override;
    int calculateOptimalOrderSize(double price, double volatility, double maxRisk) override;
    double calculateOptimalSize(const std::string &symbol) const override;
    std::vector<std::vector<double>> analyzeMarketRelationships(const std::vector<MarketDataUpdate> &marketData) override;
    std::vector<MarketDataUpdate> processMarketData(const std::vector<MarketDataUpdate> &marketData) override;

private:
    // Strategy parameters
    double deviationThreshold_ = 2.0;
    double positionLimit_ = 1000.0;
    double riskLimit_ = 1000.0;
    int lookbackPeriod_ = 20;
    std::unordered_set<std::string> watchlist_;

    // Data storage
    std::unordered_map<std::string, std::vector<double>> priceHistory_;
    std::unordered_map<std::string, std::unordered_map<std::string, double>> correlationMatrix_;

    // Internal utilities
    double calculateMovingAverage(const std::string &symbol, int period);
    double calculateStandardDeviation(const std::string &symbol, int period, double mean);
    void calculateCorrelationMatrix(const std::unordered_map<std::string, std::vector<double>> &symbolPrices);
    double calculateCorrelation(const std::vector<double> &x, const std::vector<double> &y);
    void findRelatedSecurities();
};
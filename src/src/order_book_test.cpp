// include necessary files.
#include "order_book_processor.h"
#include "risk_calculator.h"
#include "trading_strategy.h"
#include "system_monitor.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "message_bus.h"
#include "common_types.h"

// using tradingData = CT::MarketDataUpdate;
// using bookData = MDU::MarketDataUpdate;
using namespace OB;
using namespace CT_ORDER;

bookData createSampleData(const std::string &symbol, double basePrice)
{
    bookData update;

    update.symbol = symbol;
    update.lastTradePrice = basePrice;
    update.timestamp = static_cast<uint64_t>(time(nullptr)) * 1'000'000'000;

    // Add bids: prices decreasing
    update.bids.push_back(OrderBookEntry(basePrice, 100, OB::OrderSide::BUY, 0));
    update.bids.push_back(OrderBookEntry(basePrice - 0.01, 150, OB::OrderSide::BUY, 1));
    update.bids.push_back(OrderBookEntry(basePrice - 0.02, 200, OB::OrderSide::BUY, 2));
    update.bids.push_back(OrderBookEntry(basePrice - 0.03, 250, OB::OrderSide::BUY, 3));
    update.bids.push_back(OrderBookEntry(basePrice - 0.04, 300, OB::OrderSide::BUY, 4));

    // Add asks: prices increasing
    update.asks.push_back(OrderBookEntry(basePrice + 0.01, 100, OB::OrderSide::SELL, 0));
    update.asks.push_back(OrderBookEntry(basePrice + 0.02, 130, OB::OrderSide::SELL, 1));
    update.asks.push_back(OrderBookEntry(basePrice + 0.03, 160, OB::OrderSide::SELL, 2));
    update.asks.push_back(OrderBookEntry(basePrice + 0.04, 190, OB::OrderSide::SELL, 3));
    update.asks.push_back(OrderBookEntry(basePrice + 0.05, 220, OB::OrderSide::SELL, 4));

    return update;
}

MarketDataUpdate convertBookDataToMarketData(const bookData &src)
{
    MarketDataUpdate dst;
    dst.symbol = src.symbol;
    dst.bids = src.bids;
    dst.asks = src.asks;
    dst.lastTradePrice = src.lastTradePrice;
    dst.timestamp = src.timestamp;
    return dst;
}

OB::Order createSampleOrder(
    const std::string &symbol,
    OB::OrderType type,
    OB::OrderSide side,
    double price,
    int quantity)
{
    OB::Order order;
    order.symbol = symbol;
    order.type = type;
    order.side = side;
    order.price = price;
    order.quantity = quantity;
    order.timestamp = static_cast<uint64_t>(time(nullptr)) * 1'000'000'000;
    order.orderId = std::to_string(rand() % 1000000);

    return order;
}

void printOrderBook(OrderBookProcessor &processor, const std::string &symbol)
{
    std::cout << "Order Book for " << symbol << ":\n";
    std::cout << processor.getOrderBookSnapshot(symbol, 5) << std::endl;
}

void printRiskMetrics(const RiskCalculator &risk, const std::string &symbol)
{
    std::cout << "Risk Metrics for " << symbol << ":\n";
    std::cout << "Position Risk: " << risk.calculateRisk(symbol) << std::endl;
    Position pos = risk.getPosition(symbol);
    std::cout << "Current Position: " << pos.quantity << " (Max: " << pos.maxPosition << ")\n";
}

void printStrategyMetrics(const MeanReversionStrategy &strategy, const std::string &symbol)
{
    std::cout << "\nStrategy Metrics for " << symbol << ":\n";
    std::cout << "Optimal Order Size: " << strategy.calculateOptimalSize(symbol) << std::endl;
    std::cout << "Current Spread: " << strategy.calculateSpread(symbol) << std::endl;
}

int main()
{
    SystemMonitor monitor;
    OrderBookProcessor processor;
    HistoricalVaRCalculator risk;
    MeanReversionStrategy strategy("strategy");
    MessageBus bus;
    double basePrice = 150.00;

    bus.start();
    monitor.start();

    bus.subscribe("market_data", [&](const Message &msg)
                  {
                      MarketDataUpdate update = msg.getData<MarketDataUpdate>();
                      processor.processMarketDataUpdate(update); });

    bus.subscribe("order", [&](const Message &msg)
                  {
                      OB::Order order = msg.getData<OB::Order>();
                      processor.processOrder(order);

                      Position position = risk.getPosition(order.symbol);
                      position.quantity += (order.side == OB::OrderSide::BUY ? order.quantity : -order.quantity);
                      position.maxPosition = 1000;
                      risk.updatePosition(position); });

    std::cout << "===== Trading System Demonstration =====\n\n";

    // Step 1
    std::cout << "Step 1: Processing Initial Market Data\n";
    bookData update = createSampleData("AAPL", basePrice);
    processor.processMarketDataUpdate(convertBookDataToMarketData(update));
    printOrderBook(processor, update.symbol);
    printRiskMetrics(risk, update.symbol);
    std::cout << std::endl;

    // Step 2
    std::cout << "Step 2: Processing Limit Orders\n";
    OB::Order buy_order = createSampleOrder("AAPL", OB::OrderType::LIMIT, OB::OrderSide::BUY, basePrice - 0.01, 100);
    OB::Order sell_order = createSampleOrder("AAPL", OB::OrderType::LIMIT, OB::OrderSide::SELL, basePrice + 0.01, 100);
    bus.publish(Message("order", &buy_order));
    bus.publish(Message("order", &sell_order));
    printOrderBook(processor, "AAPL");
    printRiskMetrics(risk, "AAPL");

    // Step 3
    std::cout << "\nStep 3: Processing Market Order\n";
    OB::Order market_order = createSampleOrder("AAPL", OB::OrderType::MARKET, OB::OrderSide::BUY, 0.0, 50);
    bus.publish(Message("order", &market_order));
    printOrderBook(processor, "AAPL");
    printRiskMetrics(risk, "AAPL");

    // Step 4
    std::cout << "\nStep 4: Simulating Market Changes\n";
    for (int i = 0; i < 5; ++i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        basePrice += 0.01;
        bookData update = createSampleData("AAPL", basePrice);
        bus.publish(Message("market_data", &update));

        std::cout << "\nUpdate " << (i + 1) << " - New Price: " << basePrice << std::endl;
        printOrderBook(processor, "AAPL");
    }

    // Step 5
    std::cout << "\nStep 5: Generating Strategy Orders\n";
    OB::Order strategyOrder = strategy.generateOrder(convertBookDataToMarketData(update));
    bus.publish(Message("order", &strategyOrder));
    printOrderBook(processor, "AAPL");
    printRiskMetrics(risk, "AAPL");
    printStrategyMetrics(strategy, "AAPL");

    std::cout << "\nStep 6: System Health Check\n";
    std::cout << "Order Book Processor: " << (monitor.checkComponentHealth("order_book_processor") ? "Healthy" : "Unhealthy") << std::endl;
    std::cout << "Risk Calculator: " << (monitor.checkComponentHealth("order_book_processor") ? "Healthy" : "Unhealthy") << std::endl;
    std::cout << "Trading Strategy: " << (monitor.checkComponentHealth("order_book_processor") ? "Healthy" : "Unhealthy") << std::endl;
}

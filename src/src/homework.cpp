#include "order_book_processor.h"
#include "risk_calculator.h"
#include "trading_strategy.h"
#include "message_bus.h"
#include "risk_calculator.h"
#include "common_types.h"
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    /*
    Order Book Processor (15 points):

Handle order creation, modification, and cancellation
Implement price-time priority matching
Track order book state and market metrics


    */
    std::cout << "===== Trading System Demonstration =====" << std::endl;

    // Create system components
    OrderBookProcessor processor;
    RiskCalculator risk;
    MessageBus bus;

    // Initialize components
    bus.start();
    /*

    - Validate orders against position limits DONE
   - Calculate basic risk metrics DONE
   - Implement simple circuit breakers DONE

    */
    bus.subscribe("order", [&](const Message &msg)
                  {
        Order order = msg.getData<Order>();
        Position position = risk.getPosition(order.symbol);

        if (risk.validateOrder(order, position)) {
            processor.processOrder(order);

            position.quantity += (order.side == OrderSide::BUY ? order.quantity : -order.quantity);
            risk.updatePosition(position);
            std::cout << "THIS WORKED" << std::endl;
        } 
        else{
            std::cout << "SHIT DIDNT WORK" << std::endl;
        } });

    return 0;
}
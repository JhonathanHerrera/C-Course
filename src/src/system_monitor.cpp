#include "system_monitor.h"
#include <iostream>

SystemMonitor::SystemMonitor()
{

}

SystemMonitor::~SystemMonitor()
{

}

void SystemMonitor::start()
{
}

void SystemMonitor::stop()
{
}

bool SystemMonitor::checkComponentHealth(const std::string &componentName)
{
    return true;
}

void SystemMonitor::logSystemEvent(const std::string &event)
{
    std::cout << "[SystemMonitor] Event: " << event << std::endl;
}

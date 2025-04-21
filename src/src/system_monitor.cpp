#include "system_monitor.h"
#include <iostream>

SystemMonitor::SystemMonitor()
{
    // system monitoring variables would go here
    std::cout << "Looks Good!" << std::endl;
}

SystemMonitor::~SystemMonitor()
{
    // anything dynamically allocated will be deleted
}

void SystemMonitor::start()
{
}

void SystemMonitor::stop()
{
}

bool SystemMonitor::checkComponentHealth(const std::string &componentName)
{
    // obviously if it was real then implement a real system to check that
    // each part of the system is running but for the purposes of hw
    // just returning true
    return true;
}

void SystemMonitor::logSystemEvent(const std::string &event)
{
    std::cout << "[SystemMonitor] Event: " << event << std::endl;
}
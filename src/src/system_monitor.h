#pragma once
#include <string>

class SystemMonitor
{
public:
    SystemMonitor();
    ~SystemMonitor();

    void start();
    void stop();

    bool checkComponentHealth(const std::string &componentName);

    void handleComponentFailure(const std::string &component);

    void logSystemEvent(const std::string &event);
};
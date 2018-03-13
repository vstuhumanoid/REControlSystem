#ifndef LOGGER_H
#define LOGGER_H

#include "../REControlSystemInterfaces/ILogger.h"

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

class Logger : public ILogger
{
private:
    std::string _fileName;
    std::string getCurrentTime(std::string format);
public:
    Logger();
    void addMessage(std::string message, MessageTypes type) override;
};

#endif // LOGGER_H

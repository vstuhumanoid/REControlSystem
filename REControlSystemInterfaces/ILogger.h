#ifndef ILOGGER_H
#define ILOGGER_H

#include <string>

class ILogger
{
public:
    enum MessageTypes
    {
        Info,
        Error
    };

    virtual void addMessage(std::string message, MessageTypes type) = 0;
};

#endif // ILOGGER_H

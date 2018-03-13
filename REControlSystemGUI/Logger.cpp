#include "Logger.h"

std::__cxx11::string Logger::getCurrentTime(std::string format)
{
    char buffer[80];
    time_t times = time(NULL);
    tm* timeInfo = localtime(&times);
    strftime(buffer, 80, format.c_str(), timeInfo);
    return std::string(buffer);
}

Logger::Logger()
{
    _fileName = "Log_" + getCurrentTime("%d_%b_%Y_%H_%M_%S") + ".txt";
}

void Logger::addMessage(std::string message, ILogger::MessageTypes type)
{
    std::ofstream logFile;
    logFile.open(_fileName, std::ios::app);
    if(type == ILogger::Info)
        logFile << "[Info] ";
    else if(type == ILogger::Error)
        logFile << "[Error] ";
    logFile << getCurrentTime("%H:%M:%S") << " - ";
    logFile << message << std::endl;
    logFile.close();
}

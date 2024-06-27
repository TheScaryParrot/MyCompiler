#pragma once

#include <iostream>
#include <string>

static class Logger
{
   public:
    enum ELogTypes
    {
        DEBUG,
        INFO,
        WARNING,
        ERROR
    };

    void Log(std::string message, ELogTypes type);

    void SetDebug(bool debug);

   private:
    std::string ConstructLogMessage(std::string message, ELogTypes type);
    std::string GetLogTypeString(ELogTypes type);

    bool IsDebug = false;
} Logger;

void Logger::Log(std::string message, ELogTypes type)
{
    if (!IsDebug && type == ELogTypes::DEBUG)
    {
        return;
    }

    std::cout << ConstructLogMessage(message, type) << "\n";
}

void Logger::SetDebug(bool debug) { IsDebug = debug; }

std::string Logger::ConstructLogMessage(std::string message, ELogTypes type)
{
    return "[" + GetLogTypeString(type) + "] " + message;
}

std::string Logger::GetLogTypeString(ELogTypes type)
{
    switch (type)
    {
        case ELogTypes::DEBUG:
            return "DEBUG";
        case ELogTypes::INFO:
            return "INFO";
        case ELogTypes::WARNING:
            return "WARNING";
        case ELogTypes::ERROR:
            return "ERROR";
    }

    return "";
}
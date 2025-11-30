/**
 * @file logger_factory_demo.cpp
 * @brief Demonstration of the Factory Method design pattern using a Logger system.
 *
 * This example shows how to decouple client code from concrete classes by using
 * a factory method to create objects. The abstract Creator class (LoggerCreator)
 * declares a factory method that returns an abstract Product (Logger). Concrete
 * Creators override the factory method to instantiate concrete Products (FileLogger,
 * ConsoleLogger). The client code can use any Creator subclass without knowing the
 * exact type of Logger it will receive.
 *
 * Design Pattern: Factory Method
 *
 * Key Points:
 * - Abstract Product: Logger
 * - Concrete Products: FileLogger, ConsoleLogger
 * - Abstract Creator: LoggerCreator
 * - Concrete Creators: FileLoggerCreator, ConsoleLoggerCreator
 * - Client code interacts only with the Creator interface and uses log_something().
 *
 * Output Example:
 * [File] Hello World
 * [Console] Hello World
 */


#include <string>
#include <iostream>
#include <memory>

class Logger {
public:
    virtual ~Logger() = default;
    virtual void Log(const std::string&) = 0;
};

class FileLogger final : public Logger {
public:
    void Log(const std::string& msg) override {
        std::cout << "[File] " << msg << "\n";
    }
};

class ConsoleLogger final : public Logger {
public:
    void Log(const std::string& msg) override {
        std::cout << "[Console] " << msg << "\n";
    }
};

class LoggerCreator {
public:
    virtual ~LoggerCreator() = default;
    [[nodiscard]] virtual std::unique_ptr<Logger> FactoryMethod() const = 0;

    void LogSomething() const {
        auto logger = FactoryMethod();
        logger->Log("Hello world!");
    }
};

class FileLoggerCreator final : public LoggerCreator {
public:
    std::unique_ptr<Logger> FactoryMethod() const override {
        return std::make_unique<FileLogger>();
    }
};

class ConsoleLoggerCreator final : public LoggerCreator {
public:
    std::unique_ptr<Logger> FactoryMethod() const override {
        return std::make_unique<ConsoleLogger>();
    }
};

void ClientCode(const LoggerCreator& creator)
{
    creator.LogSomething();
}

int main()
{
    FileLoggerCreator fileCreator;
    ConsoleLoggerCreator consoleCreator;

    ClientCode(fileCreator);
    ClientCode(consoleCreator);
}

/**
 * @file Singleton.cpp
 * @brief Example implementation of the Singleton pattern in C++.
 *
 * The Singleton pattern ensures that a class has only one instance
 * and provides a global point of access to it.
 *
 * @details
 * **Purpose:** The pattern is used when exactly one object is needed
 * to coordinate actions across the system, such as configuration managers,
 * logging, or resource managers.
 *
 * **Pros:**
 * - Ensures a single, shared instance of a class.
 * - Provides controlled access to the instance.
 * - Can support lazy initialization (instance is created on first use).
 *
 * **Cons:**
 * - Violates the Single Responsibility Principle (SRP):
 *   the class is responsible both for its core functionality and
 *   for managing its single instance.
 * - Can make testing harder due to global state.
 * - Overuse can lead to hidden dependencies and tight coupling.
 *
 * **Thread-safety notes:**
 * - In this example, the static local variable inside `getInstance()` 
 *   ensures that the singleton is constructed safely in a multithreaded context.
 * - This approach avoids potential thread-safety issues that might arise
 *   if the singleton instance were declared as a static member of the class,
 *   because static member initialization may not be thread-safe pre-C++11.
 */


#include <utility>
#include <memory>
#include <thread>
#include <iostream>

class Singleton
{
public:
    template <typename T>
    static Singleton* getInstance(T&& val)
    {
        static std::unique_ptr<Singleton> instance{new Singleton{std::forward<T>(val)}};
        return instance.get();
    }

    // delete copy and assignment
    Singleton(const Singleton&) = delete;
    void operator=(const Singleton&) = delete;

    const std::string& getValue() const { return val_; }

private:
    template <typename T>
    Singleton(T&& val) : val_{std::forward<T>(val)}
    {
        std::cout << "Singleton constructed...\n";
    }

    // assume it's a string, for testing purposes.
    std::string val_;
};

void foo()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    auto fooInstance{Singleton::getInstance("foo")};
    std::cout << fooInstance->getValue() << std::endl;
}

void bar()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    auto barInstance{Singleton::getInstance("bar")};
    std::cout << barInstance->getValue() << std::endl;
}

int main()
{
    std::thread t1{foo};
    std::thread t2{bar};

    t1.join();
    t2.join();
}
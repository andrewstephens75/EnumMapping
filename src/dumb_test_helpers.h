#pragma once

#include <iomanip>

// These test helpers are dumb

template<class T>
void TestExpected(const std::string& name, const T& expected, const T& actual)
{
    std::cout << std::setw(60) << std::setfill('.') << std::left << name;
    if (expected == actual) {
        std::cout << "ok" << std::endl;
    } else {
        std::cout << "FAIL" << std::endl;
        std::cout << "Expected " << expected << " got " << actual << std::endl;
    }
}

template<class E>
void TestException(const std::string& name, std::function<void (void)> test)
{
    std::cout << std::setw(60) << std::setfill('.') << std::left << name;
    try {
        test();
    } catch (const E& exception) {
        std::cout << "ok" << std::endl;
        return;
    } catch (...) {
        std::cout << "FAIL" << std::endl;
        std::cout << "Some other type of exception thrown" << std::endl;
    }
    std::cout << "FAIL" << std::endl;
    std::cout << "Expected an exception" << std::endl;
}


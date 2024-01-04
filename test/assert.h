#pragma once
#include <exception>
#include "../libBuild/tmp/fmt.hpp"

class assert_exception : public std::exception
{
public:
    explicit assert_exception(const char* msg) : msg(msg) {}
    const char* what() const noexcept override { return msg; }
private:
    const char* msg;
};

template <typename LHS, typename RHS>
void assert(LHS lhs, RHS rhs)
{
    if (lhs != rhs)
    {
        throw assert_exception(tmp::fmt::Format("Assertion failed: {} != {}", lhs, rhs).c_str());
    }
}
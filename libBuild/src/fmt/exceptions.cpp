#include "fmt/exceptions.hpp"

namespace elog::fmt
{
    FormatException::FormatException(const std::string& message, const std::source_location& loc)
    : mMessage(message), mLoc(loc)
    {}

    const char* FormatException::what() const noexcept
    {
        return mMessage.c_str();
    }

    const std::source_location& FormatException::getLoc() const noexcept
    {
        return mLoc;
    }

    ArgumentException::ArgumentException(const std::string& message, const std::source_location& loc)
    : mMessage(message), mLoc(loc)
    {}

    const char* ArgumentException::what() const noexcept
    {
        return mMessage.c_str();
    }

    const std::source_location& ArgumentException::getLoc() const noexcept
    {
        return mLoc;
    }

    FormatStringException::FormatStringException(const std::string& message, const std::source_location& loc)
    : mMessage(message), mLoc(loc)
    {}

    const char* FormatStringException::what() const noexcept 
    {
        return mMessage.c_str();
    }

    const std::source_location& FormatStringException::getLoc() const noexcept
    {
        return mLoc;
    }

    TypeDeductionException::TypeDeductionException(const std::string& message, const std::source_location& loc)
    : mMessage(message), mLoc(loc)
    {}

    const char* TypeDeductionException::what() const noexcept
    {
        return mMessage.c_str();
    }

    const std::source_location& TypeDeductionException::getLoc() const noexcept
    {
        return mLoc;
    }
}
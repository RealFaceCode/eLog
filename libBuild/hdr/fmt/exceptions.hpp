#pragma once

#include <exception>
#include <string>
#include <source_location>

namespace elog::fmt
{
    class FormatException : public std::exception
    {
    public:
        FormatException(const std::string& message, const std::source_location& loc = std::source_location::current());
        const char* what() const noexcept override;
        const std::source_location& getLoc() const noexcept;

    private:
        std::string mMessage;
        std::source_location mLoc;
    };

    class ArgumentException : public std::exception
    {
    public:
        ArgumentException(const std::string& message, const std::source_location& loc = std::source_location::current());
        const char* what() const noexcept override;
        const std::source_location& getLoc() const noexcept;

    private:
        std::string mMessage;
        std::source_location mLoc;
    };

    class FormatStringException : public std::exception
    {
    public:
        FormatStringException(const std::string& message, const std::source_location& loc = std::source_location::current());
        const char* what() const noexcept override;
        const std::source_location& getLoc() const noexcept;

    private:
        std::string mMessage;
        std::source_location mLoc;
    };

    class TypeDeductionException : public std::exception
    {
    public:
        TypeDeductionException(const std::string& message, const std::source_location& loc = std::source_location::current());
        const char* what() const noexcept override;
        const std::source_location& getLoc() const noexcept;

    private:
        std::string mMessage;
        std::source_location mLoc;
    };
}
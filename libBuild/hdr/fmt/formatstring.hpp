#pragma once

#include <string>
#include <string_view>
#include <source_location>
#include <sstream>

namespace elog::fmt
{
    struct FormatString
    {
    public:
        FormatString() = default;
        FormatString(const std::string& format, const std::source_location& loc = std::source_location::current());
        FormatString(std::string_view format, const std::source_location& loc = std::source_location::current());
        FormatString(const char* format, const std::source_location& loc = std::source_location::current());
        ~FormatString() = default;

        //moveconstructor
        FormatString(FormatString&&) noexcept;
        //moveassignment
        FormatString& operator=(FormatString&&) noexcept;

        std::stringbuf format;
        std::source_location loc;
    };
}
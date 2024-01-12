#include "fmt/formatstring.hpp" 

#include <cstring>

namespace elog::fmt
{
    FormatString::FormatString(const std::string& format, const std::source_location& loc)
    : format(format), loc(loc) 
    {}

    FormatString::FormatString(std::string_view format, const std::source_location& loc)
    : loc(loc) 
    {
        this->format.sputn(format.data(), format.size());
    }

    FormatString::FormatString(const char* format, const std::source_location& loc)
    : loc(loc) 
    {
        this->format.sputn(format, strlen(format));
    }

    FormatString::FormatString(FormatString&& other) noexcept
    {
        format = std::move(other.format);
        loc = std::move(other.loc);
    }

    FormatString& FormatString::operator=(FormatString&& other) noexcept
    {
        format = std::move(other.format);
        loc = std::move(other.loc);
        return *this;
    }
}
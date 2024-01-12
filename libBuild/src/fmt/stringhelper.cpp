#include "fmt/stringhelper.hpp"

namespace elog::fmt
{
    size_t StringHasher::operator()(const std::string& key) const
    {
        return std::hash<std::string>{}(key);
    }

    size_t StringHasher::operator()(const char* key) const
    {
        return std::hash<std::string_view>{}(key);
    }

    bool StringEqual::operator()(std::string_view lhs, std::string_view rhs) const
    {
        return lhs == rhs;
    }

    bool StringEqual::operator()(std::string_view lhs, const char* rhs) const
    {
        return lhs == rhs;
    }

    bool StringEqual::operator()(const char* lhs, std::string_view rhs) const
    {
        return lhs == rhs;
    }

    bool StringEqual::operator()(const char* lhs, const char* rhs) const
    {
        return lhs == rhs;
    }
}
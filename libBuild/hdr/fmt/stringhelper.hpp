#pragma once

#include <string>
#include <string_view>

namespace elog::fmt
{
    struct StringHasher
    {
    public:
        using is_transparent = void;
        size_t operator()(const std::string& key) const;
        size_t operator()(const char* key) const;
    };

    struct StringEqual
    {
    public:
        using is_transparent = void;
        bool operator()(std::string_view lhs, std::string_view rhs) const;
        bool operator()(std::string_view lhs, const char* rhs) const;
        bool operator()(const char* lhs, std::string_view rhs) const;
        bool operator()(const char* lhs, const char* rhs) const;
    };
}
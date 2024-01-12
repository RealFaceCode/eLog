#pragma once

#include <string>
#include <vector>

namespace elog::fmt
{
    enum class FormatSpecifier
    {
        None, // no specifier
        decimal, // decimal
        hexadecimal, // hexadecimal
        Hexadecimal, // hexadecimal
        octal, // octal
        binary, // binary
        scientific, // scientific
        Scientific, // scientific
        floating, // floating
        general, // general
        General, // general
        localized, // localized
        string, // string
        character, // character
        year, // year
        month, // month
        day, // day
        hour, // hour
        minute, // minute
        second, // second
        day_of_year, // day of year
        weekday, // weekday
        Weekday, // weekday
    };

    enum class FormatAlignment
    {
        None,
        Left,
        Right,
        Center,
    };

    struct FormatType
    {
        std::string format = "";
        bool hasSpecifier = false;
        std::pair<bool, size_t> precision = {false, 0};
        std::pair<bool, size_t> index = {false, 0};
        std::pair<bool, std::pair<FormatAlignment, size_t>> alignment = {false, {FormatAlignment::None, 0}};
        std::pair<bool, FormatSpecifier> specifier = {false, FormatSpecifier::None};
    };

    struct FormatPack
    {
    public:
        size_t count = 0;
        std::vector<FormatType> formats;
    };
}
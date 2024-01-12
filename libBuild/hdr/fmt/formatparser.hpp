#pragma once

#include "formatpack.hpp"
#include <string_view>

namespace elog::fmt
{
    struct FormatParser
    {
    public:
        FormatParser() = default;
        explicit FormatParser(std::string_view format);
        ~FormatParser() = default;
        FormatPack& getFormatList();

    private:
        void parseFormat(std::string_view format);

        FormatPack mFormatStrings;
    };
}
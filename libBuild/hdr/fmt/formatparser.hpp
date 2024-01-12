#pragma once

#include "formatpack.hpp"
#include "formatstring.hpp"

namespace elog::fmt
{
    struct FormatParser
    {
    public:
        FormatParser() = default;
        explicit FormatParser(const FormatString& format);
        ~FormatParser() = default;
        FormatPack& getFormatList();

    private:
        void parseFormat(const FormatString& format);

        FormatPack mFormatStrings;
    };
}
#pragma once

#include "formatparser.hpp"
#include "formatinterpreter.hpp"
#include "argparser.hpp"
#include "formatargchecker.hpp"
#include "formatargcombiner.hpp"

#include <string_view>
#include <vector>

namespace elog::fmt
{
    template<typename... Args>
    inline std::string Format(std::string_view format, Args&& ...args)
    {
        FormatParser formatParser(format);
        FormatPack& formatList = formatParser.getFormatList();

        FormatInterpreter formatInterpreter(formatList);

        ArgParser parser(args...);
        std::vector<elog::fmt::Argument>& argList = parser.getArgList();

        FormatArgCheck formatArgCheck(format, argList, formatList);
        FormatArgCombiner formatArgCombiner(format, argList, formatList);

        return std::move(formatArgCombiner.getFormattedString());
    }
}

#pragma once

#include <string>
#include <vector>

namespace elog::fmt
{
    struct FormatString;
    struct FormatPack;
    struct Argument;
    struct FormatType;

    struct FormatArgCombiner
    {
    public:
        FormatArgCombiner() = default;
        FormatArgCombiner(const FormatString& format, std::vector<Argument>& argList, const FormatPack& formatList);
        ~FormatArgCombiner() = default;

        std::string& getFormattedString();

    private:
        void precision(Argument& argument, const FormatType& format) const;
        void alignment(Argument& argument, const FormatType& format) const;
        void reform(Argument& argument, const FormatType& format) const;
        void combine(const FormatString& format, std::vector<Argument>& argList, const FormatPack& formatList);

        std::string formattedString = "";
    };
}
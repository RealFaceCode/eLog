#pragma once

#include <string>
#include <vector>
#include <locale> // Include the <locale> header

namespace elog::fmt
{
    struct FormatString;
    struct FormatPack;
    struct Argument;
    struct FormatType;

    struct space_out : std::numpunct<char>
    {
        char do_thousands_sep() const override;
        std::string do_grouping() const override;
    };

    struct FormatArgCombiner
    {
    public:
        FormatArgCombiner() = default;
        FormatArgCombiner(std::string_view format, std::vector<Argument>& argList, const FormatPack& formatList);
        ~FormatArgCombiner() = default;

        std::string& getFormattedString();

    private:
        void precision(Argument& argument, const FormatType& format) const;
        void alignment(Argument& argument, const FormatType& format) const;
        void reform(Argument& argument, FormatType& format) const;
        void combine(std::string_view, std::vector<Argument>& argList, const FormatPack& formatList);

        std::string formattedString = "";
    };
}
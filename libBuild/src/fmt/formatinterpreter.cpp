#include "fmt/formatinterpreter.hpp"
#include "fmt/formatpack.hpp"
#include "fmt/stringhelper.hpp"
#include "fmt/generalhelper.hpp"

#include <ranges>
#include <unordered_map>
#include <set>
#include <algorithm>

namespace elog::fmt
{
    FormatInterpreter::FormatInterpreter(FormatPack& formatList)
    {
        interpret(formatList);
    }

    void FormatInterpreter::interpret(FormatPack& formatList) const
    {
        std::set<size_t> indexSet;

        for(auto& format : formatList.formats)
        {
            hasSpecifier(format);
            hasPrecision(format);
            hasAlignment(format);
            hasIndex(format);
            hasFormat(format);

            if(format.index.first)
            {
                auto [it, succes] = indexSet.insert(format.index.second);
                if(succes)
                    formatList.count++;
            }
        }
    }

    void FormatInterpreter::hasSpecifier(FormatType& formatString) const
    {
        formatString.hasSpecifier = formatString.format.find(":") != std::string::npos;
    }

    void FormatInterpreter::hasPrecision(FormatType& formatString) const
    {
        size_t pos = formatString.format.find(".");
        size_t posEnd = FindNextNonNumerical(formatString.format, pos + 1);

        if (pos != std::string::npos && posEnd != std::string::npos)
        {
            formatString.precision.first = true;
            formatString.precision.second = std::stoll(formatString.format.substr(pos + 1, posEnd - pos - 1));
        }
    }

    void FormatInterpreter::hasAlignment(FormatType& formatString) const
    {
        static const std::unordered_map<std::string, FormatAlignment, StringHasher, StringEqual> alignmentSet =
        {
            {"<", FormatAlignment::Left},
            {">", FormatAlignment::Right},
            {"^<", FormatAlignment::Center},
        };
        
        for(const auto& [key, value] : alignmentSet)
        {
            size_t pos = formatString.format.find(key);
            if(pos != std::string::npos)
            {
                formatString.alignment.first = true;
                formatString.alignment.second.first = value;
                formatString.alignment.second.second = std::stoll(formatString.format.substr(pos + key.size(), FindNextNonNumerical(formatString.format, pos + key.size()) - pos - key.size()));
                break;
            }
        }
    }

    void FormatInterpreter::hasIndex(FormatType& formatString) const
    {
        bool hasNumber = std::ranges::any_of(formatString.format, ::isdigit);
        if(hasNumber && std::isdigit(formatString.format[1]))
        {
            formatString.index.first = true;
            formatString.index.second = std::stoll(formatString.format.substr(1, FindNextNonNumerical(formatString.format, 1) - 1));
        }
    }

    void FormatInterpreter::hasFormat(FormatType& formatString) const
    {
        static const std::unordered_map<char, FormatSpecifier> formatMap =
        {
            {'d', FormatSpecifier::decimal},
            {'x', FormatSpecifier::hexadecimal},
            {'X', FormatSpecifier::Hexadecimal},
            {'o', FormatSpecifier::octal},
            {'b', FormatSpecifier::binary},
            {'e', FormatSpecifier::scientific},
            {'E', FormatSpecifier::Scientific},
            {'f', FormatSpecifier::floating},
            {'g', FormatSpecifier::general},
            {'G', FormatSpecifier::General},
            {'n', FormatSpecifier::localized},
            {'s', FormatSpecifier::string},
            {'c', FormatSpecifier::character},
            {'Y', FormatSpecifier::year},
            {'m', FormatSpecifier::month},
            {'d', FormatSpecifier::day},
            {'H', FormatSpecifier::hour},
            {'M', FormatSpecifier::minute},
            {'S', FormatSpecifier::second},
            {'j', FormatSpecifier::day_of_year},
            {'a', FormatSpecifier::weekday},
            {'A', FormatSpecifier::Weekday},
        };

        for(const auto& [key, value] : formatMap)
        {
            size_t pos = formatString.format.find(key);
            if(pos != std::string::npos)
            {
                formatString.specifier.first = true;
                formatString.specifier.second = value;
                break;
            }
        }
    }
}
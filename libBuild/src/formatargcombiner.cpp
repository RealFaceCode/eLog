#include "fmt/formatargcombiner.hpp"
#include "fmt/exceptions.hpp"
#include "fmt/formatpack.hpp"
#include "fmt/formatstring.hpp"
#include "fmt/argument.hpp"
#include "fmt/fmt.hpp"

#include <iomanip>
#include <sstream>
#include <bitset>

namespace elog::fmt
{
    FormatArgCombiner::FormatArgCombiner(const FormatString& format, std::vector<Argument>& argList, const FormatPack& formatList)
    {
        combine(format, argList, formatList);
    }

    void FormatArgCombiner::precision(Argument& arg, const FormatType& format) const
    {
        if(format.precision.first)
        {
            std::stringstream ss;
            switch (arg.type)
            {
            using enum ArgumentType;
            case None:
                break;
            case String:
                break;
            case Int:
                ss << std::right << std::setw(format.precision.second) << std::setfill('0') << arg.value.view();
                break;
            case Float:
                ss << std::setprecision(format.precision.second) << std::fixed << std::stof(arg.value.view().data());
                break;
            case Double:
                ss << std::setprecision(format.precision.second) << std::fixed << std::stod(arg.value.view().data());
                break;
            case Char:
                break;
            case Bool:
                break;
            case Pointer:
                break;
            case Container:
                break;
            default:
                break;
            }

            auto view = ss.view();
            arg.value = std::move(std::stringbuf());
            arg.value.sputn(view.data(), view.size());
        }
    }

    void FormatArgCombiner::alignment(Argument& arg, const FormatType& format) const
    {
        if(format.alignment.first)
        {
            auto argView = arg.value.view();
            std::stringstream ss;
            switch (format.alignment.second.first)
            {
            using enum FormatAlignment;
            case None:
                break;
            case Left:
                ss << std::left << std::setw(format.alignment.second.second) << std::setfill(' ') << argView;
                break;
            case Right:
                ss << std::right << std::setw(format.alignment.second.second) << std::setfill(' ') << argView;
                break;
            case Center:
            {
                size_t fill = format.alignment.second.second - arg.value.view().size();
                size_t fillLeft = fill / 2;
                size_t fillRight = fill - fillLeft;
                ss << std::left << std::setw(fillLeft) << std::setfill(' ') << "" << argView << std::setw(fillRight) << std::setfill(' ') << "";
            }
                break;
            default:
                break;
            }

            auto view = ss.view();
            arg.value = std::move(std::stringbuf());
            arg.value.sputn(view.data(), view.size());
        }
    }

    void FormatArgCombiner::reform(Argument& arg, const FormatType& format) const
    {
        if(format.specifier.first)
        {
            std::stringstream ss;
            switch (format.specifier.second)
            {
            using enum FormatSpecifier;
            case None:
                break;
            case FormatSpecifier::decimal:
                ss << arg.value.view().data();
                break;
            case FormatSpecifier::hexadecimal:
                ss << std::hex << std::stoll(arg.value.view().data());
                break;
            case FormatSpecifier::Hexadecimal:
                ss << std::hex << std::uppercase << std::stoll(arg.value.view().data());
                break;
            case FormatSpecifier::octal:
                ss << std::oct << std::stoll(arg.value.view().data());
                break;
            case FormatSpecifier::binary:
                switch(arg.type)
                {
                using enum ArgumentType;
                case None:
                    break;
                case String:
                    break;
                case Int:
                    ss << std::bitset<sizeof(long long) * 8>(std::stoll(arg.value.view().data()));
                    break;
                case Float:
                    ss << std::bitset<sizeof(float) * 8>(std::stof(arg.value.view().data()));
                    break;
                case Double:
                    ss << std::bitset<sizeof(double) * 8>(std::stod(arg.value.view().data()));
                    break;
                case Char:
                    break;
                case Bool:
                    break;
                case Pointer:
                    break;
                case Container:
                    break;
                default:
                    break;
                }
                break;
            case FormatSpecifier::scientific:
                ss << std::scientific << std::stof(arg.value.view().data());
                break;
            case FormatSpecifier::Scientific:
                ss << std::scientific << std::uppercase << std::stof(arg.value.view().data());
                break;
            case FormatSpecifier::floating:
                ss << arg.value.view().data();
                break;
            case FormatSpecifier::general:
                throw FormatException("Format specifier [general] is not supported");
                break;
            case FormatSpecifier::General:
                throw FormatException("Format specifier [General] is not supported");
                break;
            case FormatSpecifier::localized:
                ss << std::use_facet<std::numpunct<char>>(ss.getloc()).thousands_sep() << arg.value.view();
                break;
            case FormatSpecifier::string:
                ss << arg.value.view();
                break;
            case FormatSpecifier::character:
                ss << arg.value.view();
                break;
            case FormatSpecifier::year:
                throw FormatException("Format specifier [year] is not supported");
                break;
            case FormatSpecifier::month:
                throw FormatException("Format specifier [month] is not supported");
                break;
            case FormatSpecifier::day:
            throw FormatException("Format specifier [day] is not supported");
                break;
            case FormatSpecifier::hour:
                throw FormatException("Format specifier [hour] is not supported");
                break;
            case FormatSpecifier::minute:
                throw FormatException("Format specifier [minute] is not supported");
                break;
            case FormatSpecifier::second:
                throw FormatException("Format specifier [second] is not supported");
                break;
            case FormatSpecifier::day_of_year:
                throw FormatException("Format specifier [day_of_year] is not supported");
                break;
            case FormatSpecifier::weekday:
                throw FormatException("Format specifier [weekday] is not supported");
                break;
            case FormatSpecifier::Weekday:
                throw FormatException("Format specifier [Weekday] is not supported");
                break;
            default:
                break;
            }
            
            auto view = ss.view();
            arg.value = std::move(std::stringbuf());
            arg.value.sputn(view.data(), view.size());
        }

        precision(arg, format);
        alignment(arg, format);
    }

    void FormatArgCombiner::combine(const FormatString& formatString, std::vector<Argument>& argList, const FormatPack& formatList)
    {
        formattedString = formatString.format.str();
        const auto& formats = formatList.formats;
        size_t index = 0;

        for(const auto& formatType : formats)
        {
            size_t pos = formattedString.find(formatType.format);
            if(pos == std::string::npos)
                throw FormatStringException(Format("Format string [{}] is invalid", formatString.format));

            if(formatType.index.first)
                index = formatType.index.second;

            auto& arg = argList[index++];

            if(formatType.specifier.first || formatType.alignment.first || formatType.precision.first)
                reform(arg, formatType);

            formattedString.replace(pos, formatType.format.size(), arg.value.view());
        }
    }

    std::string& FormatArgCombiner::getFormattedString()
    {
        return formattedString;
    }
}
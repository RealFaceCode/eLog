#include "fmt/formatargcombiner.hpp"
#include "fmt/exceptions.hpp"
#include "fmt/formatpack.hpp"
#include "fmt/formatstring.hpp"
#include "fmt/argument.hpp"
#include "fmt/fmt.hpp"
#include "fmt/generalhelper.hpp"

#include <iomanip>
#include <sstream>
#include <bitset>

namespace elog::fmt
{

    char space_out::do_thousands_sep() const
    { 
        return '\'';
    }

    std::string space_out::do_grouping() const
    { 
        return "\3"; 
    }

    FormatArgCombiner::FormatArgCombiner(std::string_view format, std::vector<Argument>& argList, const FormatPack& formatList)
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

    void FormatArgCombiner::reform(Argument& arg, FormatType& format) const
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
            {
                auto view = arg.value.view();
                if(arg.type == ArgumentType::Double)
                    ss << std::fixed << std::scientific << (format.precision.first ? std::setprecision(format.precision.second) : std::setprecision(6)) <<  std::stod(view.data());
                else if(arg.type == ArgumentType::Float)
                    ss << std::fixed << std::scientific << (format.precision.first ? std::setprecision(format.precision.second) : std::setprecision(6)) << std::stof(view.data());
                else
                    ss << fmt::DecToScientific(std::stoll(view.data()), (format.precision.first ? format.precision.second : 6), false);

                format.precision.first = false;
                break;
            }
            case FormatSpecifier::Scientific:
            {
                auto view = arg.value.view();
                if(arg.type == ArgumentType::Double)
                    ss << std::fixed << std::scientific << std::uppercase << (format.precision.first ? std::setprecision(format.precision.second) : std::setprecision(6)) << std::uppercase << std::stod(view.data());
                else if(arg.type == ArgumentType::Float)
                    ss << std::fixed << std::scientific << std::uppercase << (format.precision.first ? std::setprecision(format.precision.second) : std::setprecision(6)) << std::uppercase << std::stof(view.data());
                else
                    ss << fmt::DecToScientific(std::stoll(view.data()), (format.precision.first ? format.precision.second : 6), true);

                format.precision.first = false;
                break;
            }
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
            {
                auto view = arg.value.view();
                ss.imbue(std::locale(ss.getloc(), new space_out));
                if(arg.type == ArgumentType::Double)
                    ss << std::fixed << std::stod(view.data());
                else if(arg.type == ArgumentType::Float)
                    ss << std::fixed << std::stof(view.data());
                else
                    ss << std::stoll(view.data());
                break;
            }
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

    void FormatArgCombiner::combine(std::string_view format, std::vector<Argument>& argList, const FormatPack& formatList)
    {
        formattedString = format;
        const auto& formats = formatList.formats;
        size_t index = 0;

        for(auto formatType : formats)
        {
            size_t pos = formattedString.find(formatType.format);
            if(pos == std::string::npos)
                throw FormatStringException(Format("Format string [{}] is invalid", format));

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
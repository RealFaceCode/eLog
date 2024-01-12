#include "fmt/formatargchecker.hpp"
#include "fmt/exceptions.hpp"
#include "fmt/fmt.hpp"
#include "fmt/formatpack.hpp"
#include "fmt/formatstring.hpp"
#include "fmt/argument.hpp"

#include <set>
#include <algorithm>

namespace elog::fmt
{
    FormatArgCheck::FormatArgCheck(const FormatString& fmt, std::vector<Argument>& argList, const FormatPack& formatList)
    : mArgList(argList), mFormatList(formatList)
    {
        check(fmt);
    }

    void FormatArgCheck::checkArgCount(const FormatString& fmt) const
    {
        if(mFormatList.count > mArgList.size())
            throw ArgumentException(Format("Too few arguments passed to format string:\n\t[{}]\nExpected [{}] arguments but got [{}] arguments",
                                            fmt.format,  mArgList.size(), mFormatList.formats.size()));
    }

    void FormatArgCheck::checkIndex()
    {
        allTrue = std::ranges::all_of(mFormatList.formats, [](const FormatType& val) { return val.index.first; });
        allFalse = std::ranges::all_of(mFormatList.formats, [](const FormatType& val) { return !val.index.first; });
        if(!allTrue && !allFalse)
            throw ArgumentException("Either all or none of the format strings must have an index");
    }

    void FormatArgCheck::checkSpecifierSwitch(FormatSpecifier formatSpecifier, ArgumentType argType, size_t index) const
    {
        switch (formatSpecifier)
            {
            using enum FormatSpecifier;
            case None:
                break;
            case FormatSpecifier::decimal:
                if(argType != ArgumentType::Int)
                    throw ArgumentException(Format("Argument [{}] is not of type [Int]", index));
                break;
            case FormatSpecifier::hexadecimal:
            case FormatSpecifier::Hexadecimal:
            case FormatSpecifier::octal:
            case FormatSpecifier::binary:
            case FormatSpecifier::scientific:
            case FormatSpecifier::Scientific:
                if(argType == ArgumentType::Container)
                    throw ArgumentException(Format("Argument [{}] is a [Container] type", index));
                break;
            case FormatSpecifier::floating:
                if(argType != ArgumentType::Float && argType != ArgumentType::Double)
                    throw ArgumentException(Format("Argument [{}] is a [Floating] type", index));
                break;
            case FormatSpecifier::general:
            case FormatSpecifier::General:
                if(argType == ArgumentType::Container)
                    throw ArgumentException(Format("Argument [{}] is a [Container] type", index));
                break;
            case FormatSpecifier::localized:
                break;
            case FormatSpecifier::string:
                if(argType != ArgumentType::String)
                    throw ArgumentException(Format("Argument [{}] is not of type [String]", index));
                break;
            case FormatSpecifier::character:
                if(argType != ArgumentType::Char)
                    throw ArgumentException(Format("Argument [{}] is not of type [Char]", index));
                break;
            case FormatSpecifier::year:
            case FormatSpecifier::month:
            case FormatSpecifier::day:
            case FormatSpecifier::hour:
            case FormatSpecifier::minute:
            case FormatSpecifier::second:
            case FormatSpecifier::day_of_year:
                if(argType != ArgumentType::Int)
                    throw ArgumentException(Format("Argument [{}] is not of type [Int]", index));
                break;
            case FormatSpecifier::weekday:
            case FormatSpecifier::Weekday:
                if(argType != ArgumentType::String)
                    throw ArgumentException(Format("Argument [{}] is not of type [String]", index));
                break;
            default:
                break;
            }
    }

    void FormatArgCheck::checkSpecifier() const
    {
        std::set<size_t> usedIndexes;
        size_t index = 0;

        for(const auto& format : mFormatList.formats)
        {
            if(allTrue)
                index = format.index.second;

            if(format.index.first && mFormatList.formats.size() == mArgList.size())
            {
                if(usedIndexes.contains(index))
                    throw ArgumentException(Format("Index [{}] is already used", index));
                else
                    usedIndexes.insert(index);
            }

            const auto& formatSpecifier = format.specifier.second;
            const auto& argType = mArgList[index].type;
            
            checkSpecifierSwitch(formatSpecifier, argType, index);

            if(allFalse)
                ++index;
        }
    }

    void FormatArgCheck::check(const FormatString& fmt)
    {
        checkArgCount(fmt);
        checkIndex();
        checkSpecifier();
    }
}
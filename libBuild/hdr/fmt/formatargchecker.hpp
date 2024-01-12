#pragma once

#include <vector>


namespace elog::fmt
{
    struct FormatString;
    struct FormatPack;
    struct Argument;

    enum class ArgumentType;
    enum class FormatSpecifier;

    struct FormatArgCheck
    {
    public:
        FormatArgCheck() = default;
        FormatArgCheck(const FormatString& fmt, std::vector<Argument>& argList, const FormatPack& formatList);
        ~FormatArgCheck() = default;

    private:
        void checkArgCount(const FormatString& fmt) const;
        void checkIndex();
        void checkSpecifierSwitch(FormatSpecifier formatSpecifier, ArgumentType argType, size_t index) const;
        void checkSpecifier() const;
        void check(const FormatString& fmt);

        bool allTrue = false;
        bool allFalse = false;
        std::vector<Argument>& mArgList;
        const FormatPack& mFormatList;
    };
}
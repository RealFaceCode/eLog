#pragma once

#include <vector>
#include <string_view>

namespace elog::fmt
{
    struct FormatPack;
    struct Argument;

    enum class ArgumentType;
    enum class FormatSpecifier;

    struct FormatArgCheck
    {
    public:
        FormatArgCheck() = default;
        FormatArgCheck(std::string_view fmt, std::vector<Argument>& argList, const FormatPack& formatList);
        ~FormatArgCheck() = default;

    private:
        void checkArgCount(std::string_view fmt) const;
        void checkIndex();
        void checkSpecifierSwitch(FormatSpecifier formatSpecifier, ArgumentType argType, size_t index) const;
        void checkSpecifier() const;
        void check(std::string_view fmt);

        bool allTrue = false;
        bool allFalse = false;
        std::vector<Argument>& mArgList;
        const FormatPack& mFormatList;
    };
}
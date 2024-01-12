#pragma once

namespace elog::fmt
{
    struct FormatPack;
    struct FormatType;

    struct FormatInterpreter
    {
    public:
        FormatInterpreter() = default;
        explicit FormatInterpreter(FormatPack& formatList);
        ~FormatInterpreter() = default;

    private:
        void interpret(FormatPack& formatList) const;
        void hasSpecifier(FormatType& formatString) const;
        void hasPrecision(FormatType& formatString) const;
        void hasAlignment(FormatType& formatString) const;
        void hasIndex(FormatType& formatString) const;
        void hasFormat(FormatType& formatString) const;
    };
}
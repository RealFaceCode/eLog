#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace elog::fmt
{
    enum class FormatAlignment;
    enum class FormatSpecifier;
    struct FormatPack;

    std::string FormatAlignmentToString(FormatAlignment alignment);
    std::string FormatSpecifierToString(FormatSpecifier specifier);
    std::vector<size_t> FindAllOf(const std::string_view& str, const std::string_view& substr);
    size_t FindNextNonNumerical(const std::string_view& str, size_t pos);
    void PrintFormatList(const FormatPack& formatList);
    std::string Date(std::string_view format = "%Y-%m-%d");
    std::string Time(std::string_view format = "%H:%M:%S");
    std::string ConvertInteger(long double num);
    std::string ConvertFractional(long double num, int precision);
    std::string DecimalToOctal(long double num, int precision);
    std::string DecToScientific(long long num, size_t precision, bool upper);
}
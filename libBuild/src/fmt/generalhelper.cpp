#include "fmt/generalhelper.hpp"
#include "fmt/formatpack.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <math.h>

namespace elog::fmt
{
    std::string FormatAlignmentToString(FormatAlignment alignment)
    {
        switch (alignment)
        {
        using enum elog::fmt::FormatAlignment;
        case None:
            return "None";
        case Left:
            return "Left";
        case Right:
            return "Right";
        case Center:
            return "Center";
        default:
            return "None";
        }
    }

    std::string FormatSpecifierToString(FormatSpecifier specifier)
    {
        switch (specifier)
        {
        using enum elog::fmt::FormatSpecifier;
        case None:
            return "None";
        case FormatSpecifier::decimal:
            return "decimal";
        case FormatSpecifier::hexadecimal:
            return "hexadecimal";
        case FormatSpecifier::Hexadecimal:
            return "Hexadecimal";
        case FormatSpecifier::octal:
            return "octal";
        case FormatSpecifier::binary:
            return "binary";
        case FormatSpecifier::scientific:
            return "scientific";
        case FormatSpecifier::Scientific:
            return "Scientific";
        case FormatSpecifier::floating:
            return "floating";
        case FormatSpecifier::general:
            return "general";
        case FormatSpecifier::General:
            return "General";
        case FormatSpecifier::localized:
            return "localized";
        case FormatSpecifier::string:
            return "string";
        case FormatSpecifier::character:
            return "character";
        case FormatSpecifier::year:
            return "year";
        case FormatSpecifier::month:
            return "month";
        case FormatSpecifier::day:
            return "day";
        case FormatSpecifier::hour:
            return "hour";
        case FormatSpecifier::minute:
            return "minute";
        case FormatSpecifier::second:
            return "second";
        case FormatSpecifier::day_of_year:
            return "day_of_year";
        case FormatSpecifier::weekday:
            return "weekday";
        case FormatSpecifier::Weekday:
            return "Weekday";
        default:
            return "None";
        }
    }

    std::vector<size_t> FindAllOf(const std::string_view& str, const std::string_view& substr)
    {
        std::vector<size_t> positions;
        size_t pos = str.find(substr, 0);

        while (pos != std::string::npos)
        {
            positions.emplace_back(pos);
            pos = str.find(substr, pos + 1);
        }

        return std::move(positions);
    }

    size_t FindNextNonNumerical(const std::string_view& str, size_t pos)
    {
        size_t i = pos;
        while (i < str.size())
        {
            if (!std::isdigit(str[i]))
            {
                return i;
            }
            ++i;
        }

        return std::string::npos;
    }

    void PrintFormatList(const FormatPack& formatList)
    {
        for (const auto& format : formatList.formats)
        {
            std::cout << "format: " << format.format << std::endl;
            std::cout << "hasSpecifier: " << (format.hasSpecifier ? "true" : "false") << std::endl;
            std::cout << "precision: " << (format.precision.first ? "true" : "false") << " " << format.precision.second << std::endl;
            std::cout << "index: " << (format.index.first ? "true" : "false") << " " << format.index.second << std::endl;
            std::cout << "alignment: " << (format.alignment.first ? "true" : "false") << " " << FormatAlignmentToString(format.alignment.second.first) << " " << format.alignment.second.second << std::endl;
            std::cout << "specifier: " << (format.specifier.first ? "true" : "false") << " " << FormatSpecifierToString(format.specifier.second) << std::endl;
            std::cout << std::endl;
        }
    }

    std::string Date(std::string_view format)
    {
        auto currentTime = std::chrono::system_clock::now();
        auto localTime = std::chrono::system_clock::to_time_t(currentTime);
        
        std::tm result;
        #ifdef _WIN32
            localtime_s(&result, &localTime);
        #else
            localtime_r(&localTime, &result);
        #endif

        std::ostringstream oss;
        oss << std::put_time(&result, format.data());
        return std::move(oss.str());
    }

    std::string Time(std::string_view format)
    {
        return std::move(Date(format));
    }

    std::string ConvertInteger(long double num)
    {
        std::string str = "";
        while (num > 0)
        {
            auto rem = static_cast<int>(num) % 8;
            str = std::to_string(rem) + str;
            num /= 8;
        }
        return std::move(str);
    }

    std::string ConvertFractional(long double num, int precision)
    {
        std::string str = ".";
        while (precision > 0)
        {
            num *= 8;
            int integer = static_cast<int>(num);
            str += std::to_string(integer);
            num -= integer;
            precision--;
        }
        return std::move(str);
    }

    std::string DecimalToOctal(long double num, int precision)
    {
        long double integer = static_cast<int>(num);
        long double dec = num - integer;
        std::string s1 = ConvertInteger(integer);
        std::string s2 = ConvertFractional(dec, precision);
        return std::move((s1 + s2));
    }

    
    std::string DecToScientific(long long num, size_t precision, bool upper)
    {
        auto exponent = (int)::log10(::fabs((double)num));
        double mantissa = (double)num / ::pow(10, exponent);

        std::stringstream ss;
        if(precision != 0)
            ss << std::setprecision(precision) << std::fixed << mantissa;
        else
            ss <<  std::setprecision(6) << std::fixed << mantissa;

        if(upper)
            ss << "E";
        else
            ss << "e";
            
        if(exponent <= 9)
            ss << "+0" << exponent;
        else
            ss << "+" << exponent;
        return std::move(ss.str());
    }
}
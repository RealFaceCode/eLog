#include "fmt/generalhelper.hpp"
#include "fmt/formatpack.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>


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
            positions.push_back(pos);
            pos = str.find(substr, pos + 1);
        }

        return positions;
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
}
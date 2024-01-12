#include "fmt/formatparser.hpp"
#include "fmt/generalhelper.hpp"
#include "fmt/exceptions.hpp"

namespace elog::fmt
{
    FormatParser::FormatParser(std::string_view format)
    {
        parseFormat(format);
    }

    FormatPack& FormatParser::getFormatList()
    {
        return mFormatStrings;
    }

    void FormatParser::parseFormat(std::string_view format)
    {
        std::vector<size_t> beginPositions = FindAllOf(format, "{");
        std::vector<size_t> endPositions = FindAllOf(format, "}");

        if (beginPositions.size() != endPositions.size())
        {
            throw FormatException("Format string is invalid");
        }

        for (size_t i = 0; i < beginPositions.size(); ++i)
        {
            size_t beginPos = beginPositions[i];
            size_t endPos = endPositions[i];
            size_t length = endPos - beginPos + 1;
            FormatType formatType;
            formatType.format = format.substr(beginPos, length);
            mFormatStrings.formats.push_back(formatType);
        }
    }
}
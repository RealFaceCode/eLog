#include "fmt/formatparser.hpp"
#include "fmt/generalhelper.hpp"
#include "fmt/exceptions.hpp"

namespace elog::fmt
{
    FormatParser::FormatParser(const FormatString& format)
    {
        parseFormat(format);
    }

    FormatPack& FormatParser::getFormatList()
    {
        return mFormatStrings;
    }

    void FormatParser::parseFormat(const FormatString& format)
    {
        std::string_view formatString = format.format.view();
        std::vector<size_t> beginPositions = FindAllOf(formatString, "{");
        std::vector<size_t> endPositions = FindAllOf(formatString, "}");

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
            formatType.format = formatString.substr(beginPos, length);
            mFormatStrings.formats.push_back(formatType);
        }
    }
}
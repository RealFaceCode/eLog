#pragma once

#include <sstream>
#include <vector>

namespace elog
{
    namespace enums
    {
        enum class Color
        {
            White,
            Black,
            Gray,
            LightRed,
            Red,
            LightGreen,
            Green,
            LightBlue,
            Blue,
            LightMagenta,
            Magenta,
            LightCyan,
            Cyan,
            LightYellow,
            Yellow,
            LightOrange,
            Orange,
            Reset,
        };

        enum class Effect
        {
            Bold,
            Underline,
            Blink,
            Reverse,
            Conceal,
            CrossedOut,
        };
    }

    namespace internal
    {
        void SetColorToState();
        std::stringbuf CreateAsciiEscapeSequence(enums::Color color, const std::vector<enums::Effect>& effect = {});
    }
}
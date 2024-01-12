#include "logcolor.hpp"
#include "state.hpp"

#include <sstream>

namespace elog::internal
{
    void SetColorToState()
    {
        auto& state = *GetState().get();
        state.logColors[enums::Color::White] = "37";
        state.logColors[enums::Color::Black] = "30";
        state.logColors[enums::Color::Gray] = "90";
        state.logColors[enums::Color::LightRed] = "91";
        state.logColors[enums::Color::Red] = "31";
        state.logColors[enums::Color::LightGreen] = "92";
        state.logColors[enums::Color::Green] = "32";
        state.logColors[enums::Color::LightBlue] = "94";
        state.logColors[enums::Color::Blue] = "34";
        state.logColors[enums::Color::LightMagenta] = "95";
        state.logColors[enums::Color::Magenta] = "35";
        state.logColors[enums::Color::LightCyan] = "96";
        state.logColors[enums::Color::Cyan] = "36";
        state.logColors[enums::Color::LightYellow] = "93";
        state.logColors[enums::Color::Yellow] = "33";
        state.logColors[enums::Color::LightOrange] = "38;5;208";
        state.logColors[enums::Color::Orange] = "38;5;202";
        state.logColors[enums::Color::Reset] = "0";

        state.logEffects[enums::Effect::Bold] = "1";
        state.logEffects[enums::Effect::Underline] = "4";
        state.logEffects[enums::Effect::Blink] = "5";
        state.logEffects[enums::Effect::Reverse] = "7";
        state.logEffects[enums::Effect::Conceal] = "8";
        state.logEffects[enums::Effect::CrossedOut] = "9";
    }

    std::stringbuf CreateAsciiEscapeSequence(enums::Color color, const std::vector<enums::Effect> &effect)
    {
        auto& state = *GetState().get();
        std::stringbuf buf;
        buf.sputn("\033[", 2);
        buf.sputn(state.logColors[color].c_str(), state.logColors[color].size());
        for(auto& e : effect)
        {
            buf.sputc(';');
            buf.sputn(state.logEffects[e].c_str(), state.logEffects[e].size());
        }
        buf.sputc('m');
        return std::move(buf);
    }
}
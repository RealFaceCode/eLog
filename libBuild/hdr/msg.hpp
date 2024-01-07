#pragma once

#include <functional>
#include <string>
#include <filesystem>

#include "fmt.hpp"
#include "state.hpp"
#include "logcolor.hpp"
#include "loglevel.hpp"

namespace elog::structs
{
    template<typename... Args>
    struct Msg
    {
    public:
        Msg() = default;
        ~Msg() = default;

        template<typename... Params>
        Msg(std::string_view logLevel, std::string_view label, const fmt::FormatString& format, Params&&... params)
        : logLevel(logLevel), label(label), format(format)
        {
            setup(std::forward<Params>(params)...);
        }

        template<typename... Params>
        void setup(Params&&... params) 
        {
            callback = [&fmt = this->format, &ll = this->logLevel, &l = this->label,params...]() -> std::string
            {
                return std::move(build(ll, l, fmt, params...));
            };
        }

        std::string execute()
        {
            return std::move(callback());
        }

    private:
        static void FillLogLevel(std::string_view logLevel, std::stringbuf& buf)
        {
            bool colorize = internal::IsFlagSet(enums::StateFlag::CLR_ON);

            if(colorize)
            {
                auto color = internal::GetLogColor(logLevel);
                if(color.has_value())
                {
                    auto const& c = color.value().get();
                    auto const& effect = c.effect;
                    auto color = internal::CreateAsciiEscapeSequence(c.color, effect);
                    auto view = color.view();
                    buf.sputn(view.data(), view.size());
                }
            }

            buf.sputn(logLevel.data(), logLevel.size());

            if(colorize)
            {
                const auto& resetColor = internal::GetResetColor();
                buf.sputn(resetColor.data(), resetColor.size());
            }

            buf.sputn("\t: ", 3);
        }

        static void FillTimeDate(std::stringbuf& buf)
        {
            if(internal::IsFlagSet(enums::StateFlag::FMT_DATE))
            {
                auto date = fmt::Date(internal::GetDateFormat());
                buf.sputn(date.data(), date.size());
                buf.sputc(' ');
            }

            if(internal::IsFlagSet(enums::StateFlag::FMT_TIME))
            {
                auto time = fmt::Time(internal::GetTimeFormat());
                buf.sputn(time.data(), time.size());
                buf.sputc(' ');
            }
        }

        static void FillLogInfo(std::stringbuf& buf, const SourceLoc& loc)
        {
            if(!internal::IsFlagSet(enums::StateFlag::FMT_FILE) 
            || !internal::IsFlagSet(enums::StateFlag::FMT_FUNCTION) 
            || !internal::IsFlagSet(enums::StateFlag::FMT_LINE))
                return;

            buf.sputc('[');
            if(internal::IsFlagSet(enums::StateFlag::FMT_FILE))
            {   
                std::filesystem::path path(loc.file_name());
                auto file = path.filename().string();
                buf.sputn(file.data(), file.size());
            }
            
            if(internal::IsFlagSet(enums::StateFlag::FMT_FUNCTION))
            {
                const char* func = loc.function_name();
                if(internal::IsFlagSet(enums::StateFlag::FMT_FILE))
                    buf.sputn(" | ", 3);
                buf.sputn(func, strlen(func));
            }

            if(internal::IsFlagSet(enums::StateFlag::FMT_LINE))
            {
                auto line = std::to_string(loc.line());
                if(internal::IsFlagSet(enums::StateFlag::FMT_FILE) || internal::IsFlagSet(enums::StateFlag::FMT_FUNCTION))
                    buf.sputn(" | ", 3);
                buf.sputn(line.data(), line.size());
            }

            buf.sputn("] ", 2);
        }

        template<typename... Params>
        static std::string build(std::string_view logLevel, std::string_view label, fmt::FormatString& format, Params&&... params)
        {
            
            std::stringbuf buf;

            FillLogLevel(logLevel, buf);
            FillTimeDate(buf);
            FillLogInfo(buf, format.loc);
            
            buf.sputn(format.format.data(), format.format.size());
            format.format = std::move(buf.str());

            return std::move(fmt::Format(format, params...));
        }

        std::string_view logLevel;
        std::string_view label;
        fmt::FormatString format;
        std::function<std::string(Args...)> callback;
    };
}
#pragma once

#include <functional>
#include <string>
#include <filesystem>

#include "fmt.hpp"

namespace elog::structs
{
    template<typename... Args>
    struct Msg
    {
    public:
        Msg() = default;
        ~Msg() = default;

        template<typename... Params>
        Msg(const fmt::FormatString& format, Params&&... params)
        : format(format)
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
        template<typename... Params>
        static std::string build(std::string_view loglevel, std::string_view label, fmt::FormatString& format, Params&&... params)
        {
            auto const& loc = format.loc;
            std::stringbuf buf;

            std::filesystem::path path(loc.file_name());
            auto file = path.filename().string();
            const char* func = loc.function_name();
            auto line = std::to_string(loc.line());

            buf.sputc('[');
            buf.sputn(file.data(), file.size());
            buf.sputn(" | ", 3);
            buf.sputn(func, strlen(func));
            buf.sputn(" | ", 3);
            buf.sputn(line.data(), line.size());
            buf.sputn("] ", 2);
            buf.sputn(format.format.data(), format.format.size());

            format.format = std::move(buf.str());

            return std::move(fmt::Format(format, params...));
        }

        fmt::FormatString format;
        std::string_view logLevel;
        std::string_view label;
        std::function<std::string(Args...)> callback;
    };
}
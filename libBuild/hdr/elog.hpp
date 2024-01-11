#pragma once

#include <vector>
#include <string>
#include <string_view>
#include "state.hpp"
#include "thread.hpp"
#include "msg.hpp"
#include "stringliteral.hpp"

namespace elog
{
    namespace internal
    {
        std::vector<std::stringbuf>& GetBuffer();
        void logOut(structs::Msg<>&& msg);
    }

    void SetLogFilePath(std::string_view path);
    void CloseFileStream();

    template<typename... Params>
    inline void LogCustom(std::string_view logLevel, std::string_view label, fmt::FormatString format, Params&&... params)
    {
        structs::Msg<> msg(logLevel, label, std::move(format), std::forward<Params>(params)...);
        if(internal::IsFlagSet(enums::StateFlag::LOG_THREAD))
            internal::AddTask(std::move(msg));
        else
            internal::logOut(std::move(msg));
    }

    template<structs::StringLiteral lit, typename... Params>
    inline void Trace(fmt::FormatString format, Params&&... params)
    {
        auto constexpr label = lit.value;
        LogCustom("TRACE", label, std::move(format), std::forward<Params>(params)...);
    }

    template<structs::StringLiteral lit, typename... Params>
    inline void Debug(fmt::FormatString format, Params&&... params)
    {
        auto constexpr label = lit.value;
        LogCustom("DEBUG", "", std::move(format), std::forward<Params>(params)...);
    }

    template<structs::StringLiteral lit, typename... Params>
    inline void Info(fmt::FormatString format, Params&&... params)
    {
        auto constexpr label = lit.value;
        LogCustom("INFO", label, std::move(format), std::forward<Params>(params)...);
    }

    template<structs::StringLiteral lit, typename... Params>
    inline void Warning(fmt::FormatString format, Params&&... params)
    {
        auto constexpr label = lit.value;
        LogCustom("WARNING", label, std::move(format), std::forward<Params>(params)...);
    }

    template<structs::StringLiteral lit, typename... Params>
    inline void Error(fmt::FormatString format, Params&&... params)
    {
        auto constexpr label = lit.value;
        LogCustom("ERROR", label, std::move(format), std::forward<Params>(params)...);
    }

    template<structs::StringLiteral lit, typename... Params>
    inline void Fatal(fmt::FormatString format, Params&&... params)
    {
        auto constexpr label = lit.value;
        LogCustom("FATAL", label, std::move(format), std::forward<Params>(params)...);
    }

    template<typename... Params>
    inline void Trace(fmt::FormatString format, Params&&... params)
    {
        LogCustom("TRACE", "", std::move(format), std::forward<Params>(params)...);
    }

    template<typename... Params>
    inline void Debug(fmt::FormatString format, Params&&... params)
    {
        LogCustom("DEBUG", "", std::move(format), std::forward<Params>(params)...);
    }

    template<typename... Params>
    inline void Info(fmt::FormatString format, Params&&... params)
    {
        LogCustom("INFO", "", std::move(format), std::forward<Params>(params)...);
    }

    template<typename... Params>
    inline void Warning(fmt::FormatString format, Params&&... params)
    {
        LogCustom("WARNING", "", std::move(format), std::forward<Params>(params)...);
    }

    template<typename... Params>
    inline void Error(fmt::FormatString format, Params&&... params)
    {
        LogCustom("ERROR", "", std::move(format), std::forward<Params>(params)...);
    }

    template<typename... Params>
    inline void Fatal(fmt::FormatString format, Params&&... params)
    {
        LogCustom("FATAL", "", std::move(format), std::forward<Params>(params)...);
    }
}
#pragma once

#include <vector>
#include <string>
#include <string_view>
#include "state.hpp"
#include "thread.hpp"
#include "msg.hpp"

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

    template<typename... Params>
    inline void Trace(std::string_view label, fmt::FormatString format, Params&&... params)
    {
        LogCustom("TRACE", label, std::move(format), std::forward<Params>(params)...);
    }

    template<typename... Params>
    inline void Debug(std::string_view label, fmt::FormatString format, Params&&... params)
    {
        LogCustom("DEBUG", label, std::move(format), std::forward<Params>(params)...);
    }

    template<typename... Params>
    inline void Info(std::string_view label, fmt::FormatString format, Params&&... params)
    {
        LogCustom("INFO", label, std::move(format), std::forward<Params>(params)...);
    }

    template<typename... Params>
    inline void Warn(std::string_view label, fmt::FormatString format, Params&&... params)
    {
        LogCustom("WARNING", label, std::move(format), std::forward<Params>(params)...);
    }

    template<typename... Params>
    inline void Error(std::string_view label, fmt::FormatString format, Params&&... params)
    {
        LogCustom("ERROR", label, std::move(format), std::forward<Params>(params)...);
    }

    template<typename... Params>
    inline void Fatal(std::string_view label, fmt::FormatString format, Params&&... params)
    {
        LogCustom("FATAL", label, std::move(format), std::forward<Params>(params)...);
    }
}
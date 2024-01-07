#pragma once

#include <vector>
#include <string>
#include <string_view>

namespace elog
{
    namespace structs
    {
        template<typename... Args>
        struct Msg;
    }

    namespace internal
    {
        std::vector<std::stringbuf>& GetBuffer();
        void logOut(structs::Msg<>&& msg);
    }

    void SetLogFilePath(std::string_view path);
    void CloseFileStream();

}
#pragma once

// Includes
#include <memory>
#include <string>
#include <string_view>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <tuple>
#include <format>
#include <sstream>
#include <cstring>
#include <filesystem>

#ifdef __clang__
#include <experimental/source_location>
    using SourceLoc = std::experimental::source_location;
#else
#include <source_location>
    using SourceLoc = std::source_location;
#endif

// defines
namespace eLog
{
    // enums
    enum class AsciiColorEnum
    {
        WHITE,
        RED,
        GREEN,
        BLUE,
        YELLOW,
        MAGENTA,
        CYAN,
        BLACK,
        GRAY,
        LIGHT_RED,
        LIGHT_GREEN,
        LIGHT_BLUE,
        LIGHT_YELLOW,
        LIGHT_MAGENTA,
        LIGHT_CYAN,
        LIGHT_GRAY,
        DARK_RED,
        DARK_GREEN,
        DARK_BLUE,
        DARK_YELLOW,
        DARK_MAGENTA,
        DARK_CYAN,
        DARK_GRAY,
        BOLD_WHITE,
        BOLD_RED,
        BOLD_GREEN,
        BOLD_BLUE,
        BOLD_YELLOW,
        BOLD_MAGENTA,
        BOLD_CYAN,
        BOLD_BLACK,
        BOLD_GRAY,
        BOLD_LIGHT_RED,
        BOLD_LIGHT_GREEN,
        BOLD_LIGHT_BLUE,
        BOLD_LIGHT_YELLOW,
        BOLD_LIGHT_MAGENTA,
        BOLD_LIGHT_CYAN,
        BOLD_LIGHT_GRAY,
        BOLD_DARK_RED,
        BOLD_DARK_GREEN,
        BOLD_DARK_BLUE,
        BOLD_DARK_YELLOW,
        BOLD_DARK_MAGENTA,
        BOLD_DARK_CYAN,
        BOLD_DARK_GRAY,
        RESET
    };

    enum class FmtFlags
    {
        NONE = 0,
        LOG_LEVEL = 1 << 0,
        LABEL = 1 << 1,
        TIME_DATE = 1 << 2,
        FILENAME = 1 << 3,
        FUNCTION = 1 << 4,
        LINE = 1 << 5,
        ALL = LOG_LEVEL | LABEL | TIME_DATE | FILENAME | FUNCTION | LINE
    };

    namespace defines
    {
        //usings
        template<typename T>
        using Ref = std::shared_ptr<T>;
        template<typename T>
        using Scope = std::unique_ptr<T>;

        template <typename T, typename... Args>
        constexpr Ref<T> makeRef(Args &&... args);

        template <typename T, typename... Args>
        constexpr Scope<T> makeScope(Args &&... args);


        template<typename... Args, std::size_t... Is>
        void apply_from_tuple(std::string& str, const std::tuple<Args...>& t, std::index_sequence<Is...>);

        template<typename... Args>
        void apply_from_tuple(std::string& str, const std::tuple<Args...>& t);

#ifdef __clang__
        using SourceLoc = std::experimental::source_location;
#else
        using SourceLoc = std::source_location;
#endif

        using String = std::string;
        using View = std::string_view;
        using StringBuf = std::stringbuf;
        using OStream = std::ostream;
        using IStream = std::istream;
        template <typename T0, typename T1>
        using Umap = std::unordered_map<T0, T1>;
        template <typename T0, typename T1>
        using Pair = std::pair<T0, T1>;
        using Path = std::filesystem::path;
        
        using Label = View;
        using LogLevel = unsigned int;
        using AsciiColor = View;
        using AsciiColorS = String;

    } // namespace defines

    namespace src
    {
        struct AsciiColor
        {
        public:
            static const defines::Umap<AsciiColorEnum, defines::AsciiColorS> mColors;
            static const defines::AsciiColorS mReset;
        };

        struct LogLevel
        {
        public:
            static defines::Umap<defines::LogLevel, defines::Pair<defines::String, defines::AsciiColorS>> mLevels;
        };

        struct Fmt
        {
        public:
            static FmtFlags mFlags;
            static defines::String mLogTDFmt;
        };
    } // namespace src

    namespace Fmt
    {
        void setFlags(FmtFlags flags);
        void setLogTDFmt(defines::View fmt);
    } // namespace Fmt

    namespace out
    {
        template <typename... Args>
        struct ArgHolder
        {
        public:
            explicit ArgHolder(Args&&... args);

            std::tuple<Args...> mArgs;
        };
        
        template <typename... Args>
        struct Msg
        {
        public:
            explicit Msg(defines::LogLevel level, defines::View msg, defines::Label label, defines::SourceLoc loc, const ArgHolder<Args...>& args);
            defines::Scope<defines::LogLevel> mLevel;
            defines::Scope<defines::StringBuf> mLabel;
            defines::Scope<defines::SourceLoc> mLoc;
            defines::Scope<defines::StringBuf> mMsg;
            defines::Scope<ArgHolder<Args...>> mArgs;
        };

        template <typename... Args>
        void FillFormat(Msg<Args...>& msg);

        void FillLogFmt(defines::StringBuf& out, const defines::Pair<defines::String, defines::AsciiColorS>& level);

        void FillLabelFmt(defines::StringBuf& out, defines::Label label);

        void FillLogInfoFmt(defines::StringBuf& out, defines::View filename, defines::View funcname, defines::View line);

        void FillTDInfoFmt(defines::StringBuf& out, defines::View fmt);

        template <typename... Args>
        void BuildMsg(defines::StringBuf& out, Msg<Args...>& msg);

        void Log(defines::OStream& stream, const defines::StringBuf& out);
    } // namespace out

    void log(defines::LogLevel level, defines::View msg, defines::Label label = "", defines::SourceLoc loc = SourceLoc::current());
    template <typename... Args>
    void logV(defines::LogLevel level, defines::View msg, out::ArgHolder<Args...> args ,defines::Label label = "", defines::SourceLoc loc = SourceLoc::current());
} // namespace eLog

// implementation
namespace eLog
{
    namespace defines
    {
        template <typename T, typename... Args>
        constexpr Ref<T> makeRef(Args&& ... args)
        {
            return std::make_shared<T>(std::forward(args...));
        }

        template <typename T, typename... Args>
        constexpr Scope<T> makeScope(Args&& ... args)
        {
            return std::make_unique<T>(std::forward(args...));
        }
        
        template<typename... Args, std::size_t... Is>
        void apply_from_tuple(std::string& str, const std::tuple<Args...>& t, std::index_sequence<Is...>)
        {
            str = std::vformat(str, std::make_format_args(std::get<Is>(t)...));
        }

        template<typename... Args>
        void apply_from_tuple(std::string& str, const std::tuple<Args...>& t)
        {
            apply_from_tuple(str, t, std::index_sequence_for<Args...>{});
        }
    } // namespace defines

    namespace src
    {
        const defines::Umap<AsciiColorEnum, defines::AsciiColorS> AsciiColor::mColors = 
        {
            {AsciiColorEnum::WHITE, "\033[0m"},
            {AsciiColorEnum::RED, "\033[0;31m"},
            {AsciiColorEnum::GREEN, "\033[0;32m"},
            {AsciiColorEnum::BLUE, "\033[0;34m"},
            {AsciiColorEnum::YELLOW, "\033[0;33m"},
            {AsciiColorEnum::MAGENTA, "\033[0;35m"},
            {AsciiColorEnum::CYAN, "\033[0;36m"},
            {AsciiColorEnum::BLACK, "\033[0;30m"},
            {AsciiColorEnum::GRAY, "\033[1;30m"},
            {AsciiColorEnum::LIGHT_RED, "\033[1;31m"},
            {AsciiColorEnum::LIGHT_GREEN, "\033[1;32m"},
            {AsciiColorEnum::LIGHT_BLUE, "\033[1;34m"},
            {AsciiColorEnum::LIGHT_YELLOW, "\033[1;33m"},
            {AsciiColorEnum::LIGHT_MAGENTA, "\033[1;35m"},
            {AsciiColorEnum::LIGHT_CYAN, "\033[1;36m"},
            {AsciiColorEnum::LIGHT_GRAY, "\033[0;37m"},
            {AsciiColorEnum::DARK_RED, "\033[0;31m"},
            {AsciiColorEnum::DARK_GREEN, "\033[0;32m"},
            {AsciiColorEnum::DARK_BLUE, "\033[0;34m"},
            {AsciiColorEnum::DARK_YELLOW, "\033[0;33m"},
            {AsciiColorEnum::DARK_MAGENTA, "\033[0;35m"},
            {AsciiColorEnum::DARK_CYAN, "\033[0;36m"},
            {AsciiColorEnum::DARK_GRAY, "\033[1;30m"},
            {AsciiColorEnum::BOLD_WHITE, "\033[1;37m"},
            {AsciiColorEnum::BOLD_RED, "\033[1;31m"},
            {AsciiColorEnum::BOLD_GREEN, "\033[1;32m"},
            {AsciiColorEnum::BOLD_BLUE, "\033[1;34m"},
            {AsciiColorEnum::BOLD_YELLOW, "\033[1;33m"},
            {AsciiColorEnum::BOLD_MAGENTA, "\033[1;35m"},
            {AsciiColorEnum::BOLD_CYAN, "\033[1;36m"},
            {AsciiColorEnum::BOLD_BLACK, "\033[1;30m"},
            {AsciiColorEnum::BOLD_GRAY, "\033[1;30m"},
            {AsciiColorEnum::BOLD_LIGHT_RED, "\033[1;31m"},
            {AsciiColorEnum::BOLD_LIGHT_GREEN, "\033[1;32m"},
            {AsciiColorEnum::BOLD_LIGHT_BLUE, "\033[1;34m"},
            {AsciiColorEnum::BOLD_LIGHT_YELLOW, "\033[1;33m"},
            {AsciiColorEnum::BOLD_LIGHT_MAGENTA, "\033[1;35m"},
            {AsciiColorEnum::BOLD_LIGHT_CYAN, "\033[1;36m"},
            {AsciiColorEnum::BOLD_LIGHT_GRAY, "\033[1;30m"},
            {AsciiColorEnum::BOLD_DARK_RED, "\033[0;31m"},
            {AsciiColorEnum::BOLD_DARK_GREEN, "\033[0;32m"},
            {AsciiColorEnum::BOLD_DARK_BLUE, "\033[0;34m"},
            {AsciiColorEnum::BOLD_DARK_YELLOW, "\033[0;33m"},
            {AsciiColorEnum::BOLD_DARK_MAGENTA, "\033[0;35m"},
            {AsciiColorEnum::BOLD_DARK_CYAN, "\033[0;36m"},
            {AsciiColorEnum::BOLD_DARK_GRAY, "\033[1;30m"},
            {AsciiColorEnum::RESET, "\033[0m"},
        };

        const defines::AsciiColorS AsciiColor::mReset = AsciiColor::mColors.at(AsciiColorEnum::RESET);

        defines::Umap<defines::LogLevel, defines::Pair<defines::String, defines::AsciiColorS>> LogLevel::mLevels = 
        {
            {0, {"TRACE", AsciiColor::mColors.at(AsciiColorEnum::BOLD_WHITE)}},
            {1, {"DEBUG", AsciiColor::mColors.at(AsciiColorEnum::BOLD_GREEN)}},
            {2, {"INFO", AsciiColor::mColors.at(AsciiColorEnum::BOLD_BLUE)}},
            {3, {"WARN", AsciiColor::mColors.at(AsciiColorEnum::BOLD_YELLOW)}},
            {4, {"ERROR", AsciiColor::mColors.at(AsciiColorEnum::BOLD_RED)}},
            {5, {"FATAL", AsciiColor::mColors.at(AsciiColorEnum::BOLD_MAGENTA)}},
        };

        FmtFlags Fmt::mFlags = FmtFlags::ALL;
        defines::String Fmt::mLogTDFmt = "%H:%M:%S %d-%m-%Y";
    } // namespace src

    namespace Fmt
    {
        void setFlags(FmtFlags flags)
        {
            src::Fmt::mFlags = flags;
        }

        void setLogTDFmt(defines::View fmt)
        {
            src::Fmt::mLogTDFmt = fmt;
        }
    } // namespace Fmt

    namespace out
    {
        template <typename... Args>
        ArgHolder<Args...>::ArgHolder(Args &&... args) : mArgs(args...) {}

        template <typename... Args>
        Msg<Args...>::Msg(defines::LogLevel level, defines::View msg, defines::Label label, defines::SourceLoc loc, const ArgHolder<Args...>& args)
        {
            defines::StringBuf msgBuf;
            msgBuf.sputn(msg.data(), msg.size());

            defines::StringBuf labelBuf;
            labelBuf.sputn(label.data(), label.size());

            mLevel = std::make_unique<defines::LogLevel>(level);
            mLabel = std::make_unique<defines::StringBuf>(std::move(labelBuf));
            mLoc = std::make_unique<defines::SourceLoc>(loc);
            mMsg = std::make_unique<defines::StringBuf>(std::move(msgBuf));
            mArgs = std::make_unique<ArgHolder<Args...>>(args);
        }

        template <typename... Args>
        void FillFormat(Msg<Args...>& msg)
        {
            if(!msg.mMsg || !msg.mArgs)
                return;

            auto view = msg.mMsg->view();

            std::string fmtMsg(view);
            defines::apply_from_tuple(fmtMsg, msg.mArgs->mArgs);

            msg.mMsg.get()->str(fmtMsg);
        }

        void FillLogFmt(defines::StringBuf& out, const defines::Pair<defines::String, defines::AsciiColorS>& level)
        {
            out.sputn(level.second.data(), level.second.size());
            out.sputn(level.first.data(), level.first.size());
            out.sputn(src::AsciiColor::mReset.data(), src::AsciiColor::mReset.size());
            out.sputn("\t : ", 4);
        }

        void FillLabelFmt(defines::StringBuf& out, defines::Label label)
        {
            out.sputc('[');
            out.sputn(label.data(), label.size());
            out.sputc(']');
        }

        void FillLogInfoFmt(defines::StringBuf& out, defines::View filename, defines::View funcname, defines::View line)
        {
            out.sputc('[');
            out.sputn(filename.data(), filename.size());
            out.sputn(" | ", 3);
            out.sputn(line.data(), line.length());
            out.sputn(" | ", 3);
            out.sputn(funcname.data(), funcname.size());
            out.sputc(']');
        }

        void FillTDInfoFmt(defines::StringBuf& out, defines::View fmt)
        {
            auto currentTime = std::chrono::system_clock::now();
            auto localTime = std::chrono::system_clock::to_time_t(currentTime);
            std::ostringstream oss;
            
            std::tm result;
            #ifdef _WIN32
                ::localtime_s(&result, &localTime);
            #else
                ::localtime_r(&localTime, &result);
            #endif
            
            oss << std::put_time(&result, fmt.data());
            auto time = oss.view();

            out.sputc('[');
            out.sputn(time.data(), time.size());
            out.sputc(']');
        }

        template <typename... Args>
        void BuildMsg(defines::StringBuf& out, Msg<Args...>& msg)
        {
            if(!msg.mLevel || !msg.mLabel || !msg.mLoc || !msg.mMsg)
                return;

            if(msg.mArgs)
                FillFormat(msg);

            auto level = src::LogLevel::mLevels.at(*msg.mLevel.get());
            auto label = msg.mLabel->view();
            auto loc = *msg.mLoc;
            auto msgStr = msg.mMsg->view();
            defines::Path path(loc.file_name());
            auto filename = path.filename().string();

            FillLogFmt(out, level);
            FillTDInfoFmt(out, src::Fmt::mLogTDFmt);
            out.sputn(" : ", 3);
            if(!label.empty())
            {
                FillLabelFmt(out, label);
                out.sputn(" : ", 3);
            }
            FillLogInfoFmt(out, filename, loc.function_name(), std::to_string(loc.line()));
            out.sputn(" : ", 3);
            out.sputn(msgStr.data(), msgStr.size());
            out.sputc('\n');
        }

        void Log(defines::OStream& stream, const defines::StringBuf& out)
        {
            auto msg = out.view();
            stream << msg;
        }
    }

    void log(defines::LogLevel level, defines::View msg, defines::Label label, defines::SourceLoc loc)
        {
            defines::StringBuf out;
            out::Msg msgObj(level, msg, label, loc, out::ArgHolder<>{});
            out::BuildMsg(out, msgObj);
            out::Log(std::cout, out);
        }

        template <typename... Args>
        void logV(defines::LogLevel level, defines::View msg, out::ArgHolder<Args...> args ,defines::Label label, defines::SourceLoc loc)
        {
            defines::StringBuf out;
            out::Msg msgObj(level, msg, label, loc, args);
            out::BuildMsg(out, msgObj);
            out::Log(std::cout, out);
        }
} // namespace eLog
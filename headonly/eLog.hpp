#pragma once

// Includes
#include <memory>
#include <string>
#include <string_view>
#include <iostream>
#include <unordered_map>

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
        
        using Label = View;
        using LogLevel = unsigned int;
        using AsciiColor = View;
        using AsciiColorS = String;

    } // namespace defines

    namespace src
    {
        struct AsciiColor
        {
            static const defines::Umap<AsciiColorEnum, defines::AsciiColorS> mColors;
            static const defines::AsciiColorS mReset;
        };

        struct LogLevel
        {
            static defines::Umap<defines::LogLevel, defines::Pair<defines::String, defines::AsciiColorS>> mLevels;
        };
    } // namespace src

    namespace out
    {
        struct Msg
        {
            defines::Scope<defines::OStream> mStream;
            defines::Scope<defines::StringBuf> mMsg;
            defines::Scope<defines::SourceLoc> mLoc;
        };
    } // namespace out
} // namespace eLog

// implementation
namespace eLog
{
    namespace defines
    {
        template <typename T, typename... Args>
        constexpr Ref<T> makeRef(Args &&... args)
        {
            return std::make_shared<T>(std::forward<Args>(args)...);
        }

        template <typename T, typename... Args>
        constexpr Scope<T> makeScope(Args &&... args)
        {
            return std::make_unique<T>(std::forward<Args>(args)...);
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
    } // namespace src
} // namespace eLog
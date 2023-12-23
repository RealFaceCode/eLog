#pragma once

// Includes
#include <memory>
#include <string>
#include <string_view>

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
    } // namespace defines
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
} // namespace eLog
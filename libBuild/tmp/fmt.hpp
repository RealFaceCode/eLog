#pragma once

#pragma region Includes

#include <string>
#include <vector>
#include <stdint.h>
#include <type_traits>
#include <source_location>
#include <sstream>
#include <iostream>
#include <array>
#include <map>
#include <utility>
#include <set>
#include <algorithm>
#include <ranges>
#include <unordered_map>
#include <string_view>
#include <cctype>
#include <locale>
#include <codecvt>
#include <functional>
#include <cmath>
#include <iomanip>
#include <bitset>
#include <cstring>

#pragma endregion

#pragma region Typedefs

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using f32 = float;
using f64 = double;

using size = size_t;

using SourceLoc = std::source_location;

template <typename T>
using not_ref_type = std::remove_reference_t<T>;

#pragma endregion

#pragma region exeptions

namespace tmp::fmt
{
    #pragma region FormatException

    class FormatException : public std::exception
    {
    public:
        FormatException(const std::string& message, const SourceLoc& loc = SourceLoc::current())
        : mMessage(message), mLoc(loc)
        {}

        const char* what() const noexcept override
        {
            return mMessage.c_str();
        }

        const SourceLoc& getLoc() const noexcept
        {
            return mLoc;
        }

    private:
        std::string mMessage;
        SourceLoc mLoc;
    };

    #pragma endregion

    #pragma region ArgumentException

    class ArgumentException : public std::exception
    {
    public:
        ArgumentException(const std::string& message, const SourceLoc& loc = SourceLoc::current())
        : mMessage(message), mLoc(loc)
        {}

        const char* what() const noexcept override
        {
            return mMessage.c_str();
        }

        const SourceLoc& getLoc() const noexcept
        {
            return mLoc;
        }

    private:
        std::string mMessage;
        SourceLoc mLoc;
    };

    #pragma endregion

    #pragma region FormatStringException

    class FormatStringException : public std::exception
    {
    public:
        FormatStringException(const std::string& message, const SourceLoc& loc = SourceLoc::current())
        : mMessage(message), mLoc(loc)
        {}

        const char* what() const noexcept override
        {
            return mMessage.c_str();
        }

        const SourceLoc& getLoc() const noexcept
        {
            return mLoc;
        }

    private:
        std::string mMessage;
        SourceLoc mLoc;
    };

    #pragma endregion
}

#pragma endregion

#pragma region constexpr variables

#pragma endregion

#pragma region constexpr checks

namespace tmp::fmt
{
    template <typename T>
    struct is_container {
        private:
            template <typename U>
            static constexpr auto test(int) -> decltype(
                    std::declval<U>().begin(), std::declval<U>().end(), std::true_type{});

            template <typename>
            static constexpr std::false_type test(...);

        public:
            static constexpr bool value = decltype(test<T>(0))::value;
    };

    template <typename T>
    constexpr bool is_container_v = is_container<T>::value;

    template <typename T>
    struct is_iterable {
        private:
            template <typename U>
            static constexpr auto test(int) -> decltype(
                    std::declval<U>().begin(), std::declval<U>().end(), ++std::declval<U>().begin(), std::true_type{});

            template <typename>
            static constexpr std::false_type test(...);

        public:
            static constexpr bool value = decltype(test<T>(0))::value;
    };

    template <typename T>
    constexpr bool is_iterable_v = is_iterable<T>::value;

    template <typename T>
    struct is_container_or_iterable {
        static constexpr bool value = is_container_v<T> || is_iterable_v<T>;
    };

    template <typename T>
    constexpr bool is_container_or_iterable_v = is_container_or_iterable<T>::value;

    template <typename T>
    struct is_container_and_iterable {
        static constexpr bool value = is_container_v<T> && is_iterable_v<T>;
    };

    template <typename T>
    constexpr bool is_container_and_iterable_v = is_container_and_iterable<T>::value;

    // check for string or string_view type
    template <typename T>
    struct is_string {
        static constexpr bool value = std::is_same_v<T, std::string>
                                    || std::is_same_v<T, const std::string>
                                    || std::is_same_v<T, std::string&>
                                    || std::is_same_v<T, const std::string&>
                                    || std::is_same_v<T, std::string*>
                                    || std::is_same_v<T, const std::string*>;
    };

    template <typename T>
    constexpr bool is_string_v = is_string<T>::value;

    template <typename T>
    struct is_string_view {
        static constexpr bool value = std::is_same_v<T, std::string_view>
                                    || std::is_same_v<T, const std::string_view>
                                    || std::is_same_v<T, std::string_view&>
                                    || std::is_same_v<T, const std::string_view&>
                                    || std::is_same_v<T, std::string_view*>
                                    || std::is_same_v<T, const std::string_view*>;
    };

    template <typename T>
    constexpr bool is_string_view_v = is_string_view<T>::value;

    template <typename T>
    struct is_string_or_string_view {
        static constexpr bool value = is_string_v<T> || is_string_view_v<T>;
    };

    template <typename T>
    constexpr bool is_string_or_string_view_v = is_string_or_string_view<T>::value;

    // check for char type
    template <typename T>
    struct is_char {
        static constexpr bool value = std::is_same_v<T, char>;
    };

    template <typename T>
    constexpr bool is_char_v = is_char<T>::value;

    template <typename T>
    struct is_const_char {
        static constexpr bool value = std::is_same_v<T, const char>;
    };

    template <typename T>
    constexpr bool is_const_char_v = is_const_char<T>::value;

    template <typename T>
    struct is_char_ptr {
        static constexpr bool value = std::is_same_v<T, char*>;
    };

    template <typename T>
    constexpr bool is_char_ptr_v = is_char_ptr<T>::value;

    template <typename T>
    struct is_const_char_ptr {
        static constexpr bool value = std::is_same_v<T, const char*>;
    };

    template <typename T>
    constexpr bool is_const_char_ptr_v = is_const_char_ptr<T>::value;

    template <typename T>
    struct is_char_array {
        static constexpr bool value = std::is_array_v<T> && std::is_same_v<std::remove_extent_t<T>, char>;
    };

    template <typename T>
    constexpr bool is_char_array_v = is_char_array<T>::value;

    template <typename T>
    struct is_const_char_array {
        static constexpr bool value = std::is_array_v<T> && std::is_same_v<std::remove_extent_t<T>, const char>;
    };

    template <typename T>
    constexpr bool is_const_char_array_v = is_const_char_array<T>::value;

    template <typename T>
    struct is_integer {
        static constexpr bool value = std::is_integral_v<T>;
    };

    template <typename T>
    constexpr bool is_integer_v = is_integer<T>::value;

    template <typename T>
    struct is_float {
        static constexpr bool value = std::is_same_v<T, float>;
    };

    template <typename T>
    constexpr bool is_float_v = is_float<T>::value;

    template <typename T>
    struct is_double {
        static constexpr bool value = std::is_same_v<T, double>;
    };

    template <typename T>
    constexpr bool is_double_v = is_double<T>::value;    

    template <typename T>
    struct is_floating_point {
        static constexpr bool value = is_float_v<T> || is_double_v<T>;
    };

    template <typename T>
    constexpr bool is_floating_point_v = is_floating_point<T>::value;

    template <typename T>
    struct is_arithmetic {
        static constexpr bool value = is_integer_v<T> || is_float_v<T>;
    };

    template <typename T>
    constexpr bool is_arithmetic_v = is_arithmetic<T>::value;

    template <typename T>
    struct is_bool {
        static constexpr bool value = std::is_same_v<T, bool>;
    };

    template <typename T>
    constexpr bool is_bool_v = is_bool<T>::value;

    template <typename T>
    struct is_pointer {
        static constexpr bool value = std::is_pointer_v<T>;
    };

    template <typename T>
    constexpr bool is_pointer_v = is_pointer<T>::value;

    template <typename T>
    struct is_nullptr {
        static constexpr bool value = std::is_same_v<T, std::nullptr_t>;
    };

    template <typename T>
    constexpr bool is_nullptr_v = is_nullptr<T>::value;

    template <typename T>
    struct is_cstring {
        static constexpr bool value = is_const_char_ptr_v<T> || is_char_ptr_v<T> || is_const_char_array_v<T> || is_char_array_v<T>;
    };

    template <typename T>
    constexpr bool is_cstring_v = is_cstring<T>::value;

    template <typename T>
    struct is_string_type {
        static constexpr bool value = is_string_or_string_view_v<T> || is_cstring_v<T>;
    };

    template <typename T>
    constexpr bool is_string_type_v = is_string_type<T>::value;

    //is_map
    template <typename T>
    struct is_map {
        private:
            template <typename U>
            static constexpr auto test(int) -> decltype(
                    std::declval<U>().begin(), std::declval<U>().end(),
                    std::declval<U>().begin()->first, std::declval<U>().begin()->second,
                    std::true_type{});

            template <typename>
            static constexpr std::false_type test(...);

        public:
            static constexpr bool value = decltype(test<T>(0))::value;
    };

    template <typename T>
    constexpr bool is_map_v = is_map<T>::value;

    //is_pair
    template <typename T>
    struct is_pair {
        private:
            template <typename U>
            static constexpr auto test(int) -> decltype(
                    std::declval<U>().first, std::declval<U>().second, std::true_type{});

            template <typename>
            static constexpr std::false_type test(...);

        public:
            static constexpr bool value = decltype(test<T>(0))::value;
    };

    template <typename T>
    constexpr bool is_pair_v = is_pair<T>::value;
}

#pragma endregion

#pragma region constexpr functions

#pragma endregion

#pragma region enums

namespace tmp::fmt
{

    #pragma region ArgumentType

    enum class ArgumentType
    {
        None,
        String,
        Int,
        Float,
        Double,
        Char,
        Bool,
        Pointer,
        Container,
    };

    #pragma endregion

    #pragma region ContainerType

    enum class ContainerType
    {
        None,
        Vector,
        Array,
        Map,
        Pair,
    };

    #pragma endregion

    #pragma region FormatSpecifier

    enum class FormatSpecifier
    {
        None, // no specifier
        decimal, // decimal
        hexadecimal, // hexadecimal
        Hexadecimal, // hexadecimal
        octal, // octal
        binary, // binary
        scientific, // scientific
        Scientific, // scientific
        floating, // floating
        general, // general
        General, // general
        localized, // localized
        string, // string
        character, // character
        year, // year
        month, // month
        day, // day
        hour, // hour
        minute, // minute
        second, // second
        day_of_year, // day of year
        weekday, // weekday
        Weekday, // weekday
    };

    #pragma endregion

    #pragma region FormatAlignment

    enum class FormatAlignment
    {
        None,
        Left,
        Right,
        Center,
    };

    #pragma endregion
}

#pragma endregion

#pragma region structs & classes declaration

namespace tmp::fmt
{
    #pragma region Helper

    struct StringHasher
    {
    public:
        using is_transparent = void;
        size operator()(const std::string& key) const;
        size operator()(const char* key) const;
    };

    struct StringEqual
    {
    public:
        using is_transparent = void;
        bool operator()(std::string_view lhs, std::string_view rhs) const;
        bool operator()(std::string_view lhs, const char* rhs) const;
        bool operator()(const char* lhs, std::string_view rhs) const;
        bool operator()(const char* lhs, const char* rhs) const;
    };

    #pragma endregion

    #pragma region Argument

    struct Argument
    {
    public:
        Argument() = default;
        Argument(const Argument&) = default;
        Argument(Argument&&) noexcept = default;
        Argument& operator=(const Argument&) = default;
        Argument& operator=(Argument&&) noexcept = default;

        void setArgumentType(ArgumentType type);

        ArgumentType type = ArgumentType::None;
        ContainerType containerType = ContainerType::None; //TODO: REMOVE?
        std::stringbuf value;
    };

    #pragma endregion

    #pragma region FormatString

    struct FormatString
    {
    public:
        FormatString() = default;
        FormatString(const std::string& format, const SourceLoc& loc = SourceLoc::current());
        FormatString(std::string_view format, const SourceLoc& loc = SourceLoc::current());
        FormatString(const char* format, const SourceLoc& loc = SourceLoc::current());

        std::string format = "";
        SourceLoc loc;
    };

    #pragma endregion

    #pragma region ArgParser

    struct ArgParser
    {
    public:
        ArgParser() = default;
        template<typename... Args>
        explicit ArgParser(Args&& ...args);

        ~ArgParser() = default;

        std::vector<Argument>& getArgList();

    private:
        template <typename Arg>
        void argToString(std::stringbuf& ss, Argument& argument, Arg& arg);

        template<typename Arg>
        void parseArg(Arg& arg);

        template<typename... Args>
        void parseArgs(Args&& ...args);

        std::vector<Argument> mArguments;
    };

    #pragma endregion

    #pragma region FormatType

    struct FormatType
    {
        std::string format = "";
        bool hasSpecifier = false;
        std::pair<bool, size> precision = {false, 0};
        std::pair<bool, size> index = {false, 0};
        std::pair<bool, std::pair<FormatAlignment, size>> alignment = {false, {FormatAlignment::None, 0}};
        std::pair<bool, FormatSpecifier> specifier = {false, FormatSpecifier::None};
    };

    #pragma endregion

    #pragma region FormatPack

    struct FormatPack
    {
    public:
        size count = 0;
        std::vector<FormatType> formats;
    };

    #pragma endregion

    #pragma region FormatParser

    struct FormatParser
    {
    public:
        FormatParser() = default;
        explicit FormatParser(const FormatString& format);

        ~FormatParser() = default;

        FormatPack& getFormatList();

    private:
        void parseFormat(const FormatString& format);

        FormatPack mFormatStrings;
    };

    #pragma endregion

    #pragma region FormatInterpreter

    struct FormatInterpreter
    {
    public:
        FormatInterpreter() = default;
        explicit FormatInterpreter(FormatPack& formatList);
        ~FormatInterpreter() = default;

    private:
        void interpret(FormatPack& formatList) const;
        void hasSpecifier(FormatType& formatString) const;
        void hasPrecision(FormatType& formatString) const;
        void hasAlignment(FormatType& formatString) const;
        void hasIndex(FormatType& formatString) const;
        void hasFormat(FormatType& formatString) const;
    };

    #pragma endregion

    #pragma region FormatArgCheck

    struct FormatArgCheck
    {
    public:
        FormatArgCheck() = default;
        FormatArgCheck(const FormatString& fmt, std::vector<Argument>& argList, const FormatPack& formatList);
        ~FormatArgCheck() = default;

    private:
        void checkArgCount(const FormatString& fmt) const;
        void checkIndex();
        void checkSpecifierSwitch(FormatSpecifier formatSpecifier, ArgumentType argType, size index) const;
        void checkSpecifier() const;
        void check(const FormatString& fmt);

        bool allTrue = false;
        bool allFalse = false;
        std::vector<Argument>& mArgList;
        const FormatPack& mFormatList;
    };
    
    #pragma endregion

    #pragma region FormatArgCombiner

    struct FormatArgCombiner
    {
    public:
        FormatArgCombiner() = default;
        FormatArgCombiner(const FormatString& format, std::vector<Argument>& argList, const FormatPack& formatList);
        ~FormatArgCombiner() = default;

        std::string& getFormattedString();

    private:
        void precision(Argument& argument, const FormatType& format) const;
        void alignment(Argument& argument, const FormatType& format) const;
        void reform(Argument& argument, const FormatType& format) const;
        void combine(const FormatString& format, std::vector<Argument>& argList, const FormatPack& formatList);

        std::string formattedString = "";
    };

    #pragma endregion
}

#pragma endregion

#pragma region functions

namespace tmp::fmt
{
    #pragma region FormatAlignmentToString && FormatSpecifierToString

    std::string FormatAlignmentToString(FormatAlignment alignment)
    {
        switch (alignment)
        {
        using enum tmp::fmt::FormatAlignment;
        case None:
            return "None";
        case Left:
            return "Left";
        case Right:
            return "Right";
        case Center:
            return "Center";
        default:
            return "None";
        }
    }

    std::string FormatSpecifierToString(FormatSpecifier specifier)
    {
        switch (specifier)
        {
        using enum tmp::fmt::FormatSpecifier;
        case None:
            return "None";
        case FormatSpecifier::decimal:
            return "decimal";
        case FormatSpecifier::hexadecimal:
            return "hexadecimal";
        case FormatSpecifier::Hexadecimal:
            return "Hexadecimal";
        case FormatSpecifier::octal:
            return "octal";
        case FormatSpecifier::binary:
            return "binary";
        case FormatSpecifier::scientific:
            return "scientific";
        case FormatSpecifier::Scientific:
            return "Scientific";
        case FormatSpecifier::floating:
            return "floating";
        case FormatSpecifier::general:
            return "general";
        case FormatSpecifier::General:
            return "General";
        case FormatSpecifier::localized:
            return "localized";
        case FormatSpecifier::string:
            return "string";
        case FormatSpecifier::character:
            return "character";
        case FormatSpecifier::year:
            return "year";
        case FormatSpecifier::month:
            return "month";
        case FormatSpecifier::day:
            return "day";
        case FormatSpecifier::hour:
            return "hour";
        case FormatSpecifier::minute:
            return "minute";
        case FormatSpecifier::second:
            return "second";
        case FormatSpecifier::day_of_year:
            return "day_of_year";
        case FormatSpecifier::weekday:
            return "weekday";
        case FormatSpecifier::Weekday:
            return "Weekday";
        default:
            return "None";
        }
    }

    #pragma endregion

    #pragma region Helper

    std::vector<size> FindAllOf(const std::string_view& str, const std::string_view& substr)
    {
        std::vector<size> positions;
        size pos = str.find(substr, 0);

        while (pos != std::string::npos)
        {
            positions.push_back(pos);
            pos = str.find(substr, pos + 1);
        }

        return positions;
    }

    size FindNextNonNumerical(const std::string_view& str, size pos)
    {
        size i = pos;
        while (i < str.size())
        {
            if (!std::isdigit(str[i]))
            {
                return i;
            }
            ++i;
        }

        return std::string::npos;
    }

    void PrintFormatList(const FormatPack& formatList)
    {
        for (const auto& format : formatList.formats)
        {
            std::cout << "format: " << format.format << std::endl;
            std::cout << "hasSpecifier: " << (format.hasSpecifier ? "true" : "false") << std::endl;
            std::cout << "precision: " << (format.precision.first ? "true" : "false") << " " << format.precision.second << std::endl;
            std::cout << "index: " << (format.index.first ? "true" : "false") << " " << format.index.second << std::endl;
            std::cout << "alignment: " << (format.alignment.first ? "true" : "false") << " " << FormatAlignmentToString(format.alignment.second.first) << " " << format.alignment.second.second << std::endl;
            std::cout << "specifier: " << (format.specifier.first ? "true" : "false") << " " << FormatSpecifierToString(format.specifier.second) << std::endl;
            std::cout << std::endl;
        }
    }

    #pragma endregion

    #pragma region Format

    template<typename... Args>
    std::string Format(const FormatString& format, Args&& ...args)
    {
        FormatParser formatParser(format);
        FormatPack& formatList = formatParser.getFormatList();

        FormatInterpreter formatInterpreter(formatList);

        ArgParser parser(args...);
        std::vector<tmp::fmt::Argument>& argList = parser.getArgList();

        FormatArgCheck formatArgCheck(format, argList, formatList);
        FormatArgCombiner formatArgCombiner(format, argList, formatList);

        return std::move(formatArgCombiner.getFormattedString());
    }

    #pragma endregion
}

#pragma endregion

#pragma region structs & classes implementation

namespace tmp::fmt
{
    #pragma region Helper

    size StringHasher::operator()(const std::string& key) const
    {
        return std::hash<std::string>{}(key);
    }

    size StringHasher::operator()(const char* key) const
    {
        return std::hash<std::string_view>{}(key);
    }

    bool StringEqual::operator()(std::string_view lhs, std::string_view rhs) const
    {
        return lhs == rhs;
    }

    bool StringEqual::operator()(std::string_view lhs, const char* rhs) const
    {
        return lhs == rhs;
    }

    bool StringEqual::operator()(const char* lhs, std::string_view rhs) const
    {
        return lhs == rhs;
    }

    bool StringEqual::operator()(const char* lhs, const char* rhs) const
    {
        return lhs == rhs;
    }

    #pragma endregion

    #pragma region Argument

    void Argument::setArgumentType(ArgumentType type)
    {
        if(this->type == ArgumentType::None)
            this->type = type;
    }

    #pragma endregion

    #pragma region FormatString

    FormatString::FormatString(const std::string& format, const SourceLoc& loc)
    : format(format), loc(loc) 
    {}

    FormatString::FormatString(std::string_view format, const SourceLoc& loc)
    : format(format), loc(loc) 
    {}

    FormatString::FormatString(const char* format, const SourceLoc& loc)
    : format(format), loc(loc) 
    {}

    #pragma endregion

    #pragma region ArgParser

    template<typename... Args>
    ArgParser::ArgParser(Args&& ...args)
    {
        parseArgs(args...);
    }

    std::vector<Argument>& ArgParser::getArgList()
    {
        return mArguments;
    }

    template <typename Arg>
    void ArgParser::argToString(std::stringbuf& buf, Argument& argument, Arg& arg)
    {
        if constexpr (is_string_type_v<not_ref_type<Arg>>)
        {
            argument.setArgumentType(ArgumentType::String);
            if constexpr (is_cstring_v<not_ref_type<Arg>>)
            {
                buf.sputn(arg, strlen(arg));
            }
            else
            {
                buf.sputn(arg.data(), arg.size());
            }
        }
        else if constexpr (is_integer_v<not_ref_type<Arg>>)
        {
            argument.setArgumentType(ArgumentType::Int);
            auto r = std::to_string(arg);
            buf.sputn(r.data(), r.size());
        }
        else if constexpr (is_float_v<not_ref_type<Arg>>)
        {
            argument.setArgumentType(ArgumentType::Float);
            auto r = std::to_string(arg);
            buf.sputn(r.data(), r.size());
        }
        else if constexpr (is_double_v<not_ref_type<Arg>>)
        {
            argument.setArgumentType(ArgumentType::Double);
            auto r = std::to_string(arg);
            buf.sputn(r.data(), r.size());
        }
        else if constexpr (is_bool_v<not_ref_type<Arg>>)
        {
            argument.setArgumentType(ArgumentType::Bool);
            auto r = std::to_string(arg);
            buf.sputn(r.data(), r.size());
        }
        else if constexpr (is_pointer_v<not_ref_type<Arg>>)
        {
            argument.setArgumentType(ArgumentType::Pointer);
            auto r = std::to_string((uintptr_t)arg);
            buf.sputn(r.data(), r.size());
        }
        else if constexpr (is_container_v<not_ref_type<Arg>> && !is_string_type_v<not_ref_type<Arg>>)
        {
            argument.setArgumentType(ArgumentType::Container);

            buf.sputc('[');
            for(auto& element : arg)
            {
                if constexpr (is_container_v<decltype(element)> || is_pair_v<decltype(element)>)
                {
                    argToString(buf, argument, element);
                    if(element != arg.back())
                        buf.sputn(", ", 2);
                }
                else
                {
                    if(element != arg.back())
                    {
                        argToString(buf, argument, element);
                        buf.sputc(',');
                    }
                    else
                        argToString(buf, argument, element);
                }
            }
            buf.sputc(']');
        }
        else if constexpr (is_pair_v<not_ref_type<Arg>>)
        {
            argument.setArgumentType(ArgumentType::Container);
            argument.containerType = ContainerType::Pair;

            buf.sputn("[First: ", 8);
            argToString(buf, argument, arg.first);
            buf.sputn(", Second: ", 10);
            argToString(buf, argument, arg.second);
            buf.sputc(']');	
        }
        else
        {
            throw ArgumentException("Argument type not supported");
        }
    }

    template<typename Arg>
    void ArgParser::parseArg(Arg& arg)
    {
        Argument argument;
        std::stringbuf buf;
        
        argToString(buf, argument, arg);

        argument.value = std::move(buf);
        mArguments.push_back(std::move(argument));
    }

    template<typename... Args>
    void ArgParser::parseArgs(Args&& ...args)
    {
        size numArgs = sizeof...(Args);
        if(numArgs == 0)
            return;

        mArguments.reserve(numArgs);

        (parseArg(args), ...);
    }

    #pragma endregion

    #pragma region FormatParser

    FormatParser::FormatParser(const FormatString& format)
    {
        parseFormat(format);
    }

    FormatPack& FormatParser::getFormatList()
    {
        return mFormatStrings;
    }

    void FormatParser::parseFormat(const FormatString& format)
    {
        std::string formatString = format.format;
        std::vector<size> beginPositions = FindAllOf(formatString, "{");
        std::vector<size> endPositions = FindAllOf(formatString, "}");

        if (beginPositions.size() != endPositions.size())
        {
            throw FormatException("Format string is invalid");
        }

        for (size i = 0; i < beginPositions.size(); ++i)
        {
            size beginPos = beginPositions[i];
            size endPos = endPositions[i];
            size length = endPos - beginPos + 1;
            FormatType formatType;
            formatType.format = formatString.substr(beginPos, length);
            mFormatStrings.formats.push_back(formatType);
        }
    }

    #pragma endregion

    #pragma region FormatInterpreter

    FormatInterpreter::FormatInterpreter(FormatPack& formatList)
    {
        interpret(formatList);
    }

    void FormatInterpreter::interpret(FormatPack& formatList) const
    {
        std::set<size> indexSet;

        for(auto& format : formatList.formats)
        {
            hasSpecifier(format);
            hasPrecision(format);
            hasAlignment(format);
            hasIndex(format);
            hasFormat(format);

            if(format.index.first)
            {
                auto [it, succes] = indexSet.insert(format.index.second);
                if(succes)
                    formatList.count++;
            }
        }
    }

    void FormatInterpreter::hasSpecifier(FormatType& formatString) const
    {
        formatString.hasSpecifier = formatString.format.find(":") != std::string::npos;
    }

    void FormatInterpreter::hasPrecision(FormatType& formatString) const
    {
        size pos = formatString.format.find(".");
        size posEnd = FindNextNonNumerical(formatString.format, pos + 1);

        if (pos != std::string::npos && posEnd != std::string::npos)
        {
            formatString.precision.first = true;
            formatString.precision.second = std::stoll(formatString.format.substr(pos + 1, posEnd - pos - 1));
        }
    }

    void FormatInterpreter::hasAlignment(FormatType& formatString) const
    {
        static const std::unordered_map<std::string, FormatAlignment, StringHasher, StringEqual> alignmentSet =
        {
            {"<", FormatAlignment::Left},
            {">", FormatAlignment::Right},
            {"^<", FormatAlignment::Center},
        };
        
        for(const auto& [key, value] : alignmentSet)
        {
            size pos = formatString.format.find(key);
            if(pos != std::string::npos)
            {
                formatString.alignment.first = true;
                formatString.alignment.second.first = value;
                formatString.alignment.second.second = std::stoll(formatString.format.substr(pos + key.size(), FindNextNonNumerical(formatString.format, pos + key.size()) - pos - key.size()));
                break;
            }
        }
    }

    void FormatInterpreter::hasIndex(FormatType& formatString) const
    {
        bool hasNumber = std::ranges::any_of(formatString.format, ::isdigit);
        if(hasNumber && std::isdigit(formatString.format[1]))
        {
            formatString.index.first = true;
            formatString.index.second = std::stoll(formatString.format.substr(1, FindNextNonNumerical(formatString.format, 1) - 1));
        }
    }

    void FormatInterpreter::hasFormat(FormatType& formatString) const
    {
        static const std::unordered_map<char, FormatSpecifier> formatMap =
        {
            {'d', FormatSpecifier::decimal},
            {'x', FormatSpecifier::hexadecimal},
            {'X', FormatSpecifier::Hexadecimal},
            {'o', FormatSpecifier::octal},
            {'b', FormatSpecifier::binary},
            {'e', FormatSpecifier::scientific},
            {'E', FormatSpecifier::Scientific},
            {'f', FormatSpecifier::floating},
            {'g', FormatSpecifier::general},
            {'G', FormatSpecifier::General},
            {'L', FormatSpecifier::localized},
            {'s', FormatSpecifier::string},
            {'c', FormatSpecifier::character},
            {'Y', FormatSpecifier::year},
            {'m', FormatSpecifier::month},
            {'d', FormatSpecifier::day},
            {'H', FormatSpecifier::hour},
            {'M', FormatSpecifier::minute},
            {'S', FormatSpecifier::second},
            {'j', FormatSpecifier::day_of_year},
            {'a', FormatSpecifier::weekday},
            {'A', FormatSpecifier::Weekday},
        };

        for(const auto& [key, value] : formatMap)
        {
            size pos = formatString.format.find(key);
            if(pos != std::string::npos)
            {
                formatString.specifier.first = true;
                formatString.specifier.second = value;
                break;
            }
        }
    }

    #pragma endregion

    #pragma region FormatArgCheckAndFormer

    FormatArgCheck::FormatArgCheck(const FormatString& fmt, std::vector<Argument>& argList, const FormatPack& formatList)
    : mArgList(argList), mFormatList(formatList)
    {
        check(fmt);
    }

    void FormatArgCheck::checkArgCount(const FormatString& fmt) const
    {
        if(mFormatList.count > mArgList.size())
            throw ArgumentException(Format("Too few arguments passed to format string:\n\t[{}]\nExpected [{}] arguments but got [{}] arguments",
                                            fmt.format,  mArgList.size(), mFormatList.formats.size()));
    }

    void FormatArgCheck::checkIndex()
    {
        allTrue = std::ranges::all_of(mFormatList.formats, [](const FormatType& val) { return val.index.first; });
        allFalse = std::ranges::all_of(mFormatList.formats, [](const FormatType& val) { return !val.index.first; });
        if(!allTrue && !allFalse)
            throw ArgumentException("Either all or none of the format strings must have an index");
    }

    void FormatArgCheck::checkSpecifierSwitch(FormatSpecifier formatSpecifier, ArgumentType argType, size index) const
    {
        switch (formatSpecifier)
            {
            using enum FormatSpecifier;
            case None:
                break;
            case FormatSpecifier::decimal:
                if(argType != ArgumentType::Int)
                    throw ArgumentException(Format("Argument [{}] is not of type [Int]", index));
                break;
            case FormatSpecifier::hexadecimal:
            case FormatSpecifier::Hexadecimal:
            case FormatSpecifier::octal:
            case FormatSpecifier::binary:
            case FormatSpecifier::scientific:
            case FormatSpecifier::Scientific:
                if(argType == ArgumentType::Container)
                    throw ArgumentException(Format("Argument [{}] is a [Container] type", index));
                break;
            case FormatSpecifier::floating:
                if(argType != ArgumentType::Float && argType != ArgumentType::Double)
                    throw ArgumentException(Format("Argument [{}] is a [Floating] type", index));
                break;
            case FormatSpecifier::general:
            case FormatSpecifier::General:
                if(argType == ArgumentType::Container)
                    throw ArgumentException(Format("Argument [{}] is a [Container] type", index));
                break;
            case FormatSpecifier::localized:
                break;
            case FormatSpecifier::string:
                if(argType != ArgumentType::String)
                    throw ArgumentException(Format("Argument [{}] is not of type [String]", index));
                break;
            case FormatSpecifier::character:
                if(argType != ArgumentType::Char)
                    throw ArgumentException(Format("Argument [{}] is not of type [Char]", index));
                break;
            case FormatSpecifier::year:
            case FormatSpecifier::month:
            case FormatSpecifier::day:
            case FormatSpecifier::hour:
            case FormatSpecifier::minute:
            case FormatSpecifier::second:
            case FormatSpecifier::day_of_year:
                if(argType != ArgumentType::Int)
                    throw ArgumentException(Format("Argument [{}] is not of type [Int]", index));
                break;
            case FormatSpecifier::weekday:
            case FormatSpecifier::Weekday:
                if(argType != ArgumentType::String)
                    throw ArgumentException(Format("Argument [{}] is not of type [String]", index));
                break;
            default:
                break;
            }
    }

    void FormatArgCheck::checkSpecifier() const
    {
        std::set<size> usedIndexes;
        size index = 0;

        for(const auto& format : mFormatList.formats)
        {
            if(allTrue)
                index = format.index.second;

            if(format.index.first && mFormatList.formats.size() == mArgList.size())
            {
                if(usedIndexes.contains(index))
                    throw ArgumentException(Format("Index [{}] is already used", index));
                else
                    usedIndexes.insert(index);
            }

            const auto& formatSpecifier = format.specifier.second;
            const auto& argType = mArgList[index].type;
            
            checkSpecifierSwitch(formatSpecifier, argType, index);

            if(allFalse)
                ++index;
        }
    }

    void FormatArgCheck::check(const FormatString& fmt)
    {
        checkArgCount(fmt);
        checkIndex();
        checkSpecifier();
    }

    #pragma endregion

    #pragma region FormatArgCombiner

    FormatArgCombiner::FormatArgCombiner(const FormatString& format, std::vector<Argument>& argList, const FormatPack& formatList)
    {
        combine(format, argList, formatList);
    }

    void FormatArgCombiner::precision(Argument& arg, const FormatType& format) const
    {
        if(format.precision.first)
        {
            std::stringstream ss;
            switch (arg.type)
            {
            using enum ArgumentType;
            case None:
                break;
            case String:
                break;
            case Int:
                ss << std::right << std::setw(format.precision.second) << std::setfill('0') << arg.value.view();
                break;
            case Float:
                ss << std::setprecision(format.precision.second) << std::fixed << std::stof(arg.value.view().data());
                break;
            case Double:
                ss << std::setprecision(format.precision.second) << std::fixed << std::stod(arg.value.view().data());
                break;
            case Char:
                break;
            case Bool:
                break;
            case Pointer:
                break;
            case Container:
                break;
            default:
                break;
            }

            auto view = ss.view();
            arg.value = std::move(std::stringbuf());
            arg.value.sputn(view.data(), view.size());
        }
    }

    void FormatArgCombiner::alignment(Argument& arg, const FormatType& format) const
    {
        if(format.alignment.first)
        {
            std::stringstream ss;
            switch (format.alignment.second.first)
            {
            using enum FormatAlignment;
            case None:
                break;
            case Left:
                ss << std::left << std::setw(format.alignment.second.second) << arg.value.view();
                break;
            case Right:
                ss << std::right << std::setw(format.alignment.second.second) << arg.value.view();
                break;
            case Center:
            {
                size fill = format.alignment.second.second - arg.value.view().size();
                size fillLeft = fill / 2;
                size fillRight = fill - fillLeft;
                ss << std::left << std::setw(fillLeft) << std::setfill(' ') << "" << arg.value.view() << std::setw(fillRight) << std::setfill(' ') << "";
            }
                break;
            default:
                break;
            }

            auto view = ss.view();
            arg.value = std::move(std::stringbuf());
            arg.value.sputn(view.data(), view.size());
        }
    }

    void FormatArgCombiner::reform(Argument& arg, const FormatType& format) const
    {
        if(format.specifier.first)
        {
            std::stringstream ss;
            switch (format.specifier.second)
            {
            using enum FormatSpecifier;
            case None:
                break;
            case FormatSpecifier::decimal:
                break;
            case FormatSpecifier::hexadecimal:
                ss << std::hex << std::stoll(arg.value.view().data());
                break;
            case FormatSpecifier::Hexadecimal:
                ss << std::hex << std::uppercase << std::stoll(arg.value.view().data());
                break;
            case FormatSpecifier::octal:
                ss << std::oct << std::stoll(arg.value.view().data());
                break;
            case FormatSpecifier::binary:
                ss << std::bitset<sizeof(long long) * 8>(std::stoll(arg.value.view().data()));
                break;
            case FormatSpecifier::scientific:
                ss << std::scientific << std::stof(arg.value.view().data());
                break;
            case FormatSpecifier::Scientific:
                ss << std::scientific << std::uppercase << std::stof(arg.value.view().data());
                break;
            case FormatSpecifier::floating:
                break;
            case FormatSpecifier::general:
                throw FormatException("Format specifier [general] is not supported");
                break;
            case FormatSpecifier::General:
                throw FormatException("Format specifier [General] is not supported");
                break;
            case FormatSpecifier::localized:
                ss << std::use_facet<std::numpunct<char>>(ss.getloc()).thousands_sep() << arg.value.view();
                break;
            case FormatSpecifier::string:
                break;
            case FormatSpecifier::character:
                break;
            case FormatSpecifier::year:
                throw FormatException("Format specifier [year] is not supported");
                break;
            case FormatSpecifier::month:
                throw FormatException("Format specifier [month] is not supported");
                break;
            case FormatSpecifier::day:
            throw FormatException("Format specifier [day] is not supported");
                break;
            case FormatSpecifier::hour:
                throw FormatException("Format specifier [hour] is not supported");
                break;
            case FormatSpecifier::minute:
                throw FormatException("Format specifier [minute] is not supported");
                break;
            case FormatSpecifier::second:
                throw FormatException("Format specifier [second] is not supported");
                break;
            case FormatSpecifier::day_of_year:
                throw FormatException("Format specifier [day_of_year] is not supported");
                break;
            case FormatSpecifier::weekday:
                throw FormatException("Format specifier [weekday] is not supported");
                break;
            case FormatSpecifier::Weekday:
                throw FormatException("Format specifier [Weekday] is not supported");
                break;
            default:
                break;
            }
            
            auto view = ss.view();
            arg.value = std::move(std::stringbuf());
            arg.value.sputn(view.data(), view.size());
        }

        precision(arg, format);
        alignment(arg, format);
    }

    void FormatArgCombiner::combine(const FormatString& formatString, std::vector<Argument>& argList, const FormatPack& formatList)
    {
        formattedString = formatString.format;
        const auto& formats = formatList.formats;
        size index = 0;

        for(const auto& formatType : formats)
        {
            size pos = formattedString.find(formatType.format);
            if(pos == std::string::npos)
                throw FormatStringException(Format("Format string [{}] is invalid", formatString.format));

            if(formatType.index.first)
                index = formatType.index.second;

            auto& arg = argList[index++];

            if(formatType.specifier.first || formatType.alignment.first || formatType.precision.first)
                reform(arg, formatType);

            formattedString.replace(pos, formatType.format.size(), arg.value.view());
        }
    }

    std::string& FormatArgCombiner::getFormattedString()
    {
        return formattedString;
    }

    #pragma endregion
}

#pragma endregion

#pragma once

#include <type_traits>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <iostream>
#include <string_view>
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <iomanip>
#include <set>
#include <bitset>
#include <cmath>

namespace eLog::fmt
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
        static constexpr bool value = (std::is_same_v<T, std::string> 
                                    || std::is_same_v<T, std::string_view> 
                                    || std::is_same_v<T, const char*> 
                                    || std::is_same_v<T, char*> 
                                    || std::is_same_v<T, const char[]> 
                                    || std::is_same_v<T, char[]> 
                                    || std::is_same_v<T, char> 
                                    || std::is_same_v<T, const char>);
    };

    template <typename T>
    constexpr bool is_string_v = is_string<T>::value;

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

    const std::set<char> numberFormatSet = {'d', 'x', 'X', 'o', 'b', 'e', 'E', 'f', 'g', 'G', 'n'};
    const std::set<char> stringFormatSet = {'s', 'c'};
    const std::set<std::string> alignmentSet = {"<", "^<", ">"};
    const std::set<char> precisionSet = {'.'};
    const std::set<char> timeFormatSet = {'y', 'm', 'd', 'H', 'M', 'S', 'j', 'A', 'a'};

    struct space_out : std::numpunct<char>
    {
      char do_thousands_sep() const override { return '\''; } // setzt den Tausendertrennzeichen auf '.'
      std::string do_grouping() const override { return "\3"; } // Gruppen von drei Ziffern
    };

    template <typename LHS, typename RHS>
    void assert(const LHS& lhs, const RHS& rhs)
    {
        if(lhs != rhs)
            throw std::runtime_error("Assertion failed");
    }

    // Funktion zur Konvertierung des Ganzzahlteils
    auto convertInteger(long double num)
    {
        std::string str = "";
        while (num > 0)
        {
            auto rem = static_cast<int>(num) % 8;
            str = std::to_string(rem) + str;
            num /= 8;
        }
        return str;
    }

    // Funktion zur Konvertierung des Bruchtelparts
    auto convertFractional(long double num, int precision)
    {
        std::string str = ".";
        while (precision > 0)
        {
            num *= 8;
            int integer = static_cast<int>(num);
            str += std::to_string(integer);
            num -= integer;
            precision--;
        }
        return str;
    }

    // Funktion zur Konvertierung der Fließkommazahl in Oktalzahl
    std::string decimalToOctal(long double num, int precision)
    {
        long double integer = static_cast<int>(num);
        long double dec = num - integer;
        std::string s1 = convertInteger(integer);
        std::string s2 = convertFractional(dec, precision);
        return s1 + s2;
    }

    std::vector<size_t> findPositions(const std::string& str, const std::string& subStr)
    {
        std::vector<size_t> result;

        size_t pos = 0;
        while ((pos = str.find(subStr, pos)) != std::string::npos) {
            result.push_back(pos);
            pos += subStr.length();
        }

        return result;
    }

    bool ContainsNumeric(std::string_view str)
    {
        return std::ranges::any_of(str, ::isdigit);
    }

    bool ContainsChars(std::string_view str, std::string_view chars)
    {
        bool result = false;
        for(auto& c : chars)
        {
            if(str.find(c) != std::string::npos && c != '\0')
            {
                result = true;
            }
            else
            {
                return false;
            }
        }
        return result;
    }

    template <typename T>
    void containerToString(std::stringstream& ss, const T& container)
    {
        if constexpr (is_string_v<T>)
        {
            ss << container;
            return;
        }

        ss << "[";
        for(auto& item : container)
        {
            if constexpr (is_container_v<decltype(item)> && !is_string_v<decltype(item)>)
            {
                if(item != container.back())
                {
                    containerToString(ss, item);
                    ss << ", ";
                }
                else
                    containerToString(ss, item);
            }
            else 
            {
            if(item != container.back())
                ss << item << ", ";
            else
                ss << item;
            }
        }
        ss << "]";
    }

    template <typename T>
    void containerAndArgToString(std::vector<std::string>& result, size_t& count,  const T& container)
    {
        std::stringstream str;

        if constexpr (!is_string_v<T> && is_container_v<T>)
        {
            str << "[";
            for(auto& item : container)
            {
                if constexpr (is_container_v<decltype(item)>)
                {   
                    if(item != container.back())
                    {
                        containerToString(str, item);
                        str << ", ";
                    }
                    else
                        containerToString(str, item);
                }
                else 
                {
                if(item != container.back())
                    str << item << ", ";
                else
                    str << item;
                }
            }
            str << "]";
            result.push_back(str.str());
        }
        else
        {
            str << container;
            result.push_back(str.str());
        }
        count++;
    }

    auto HasSpecifier(std::string_view str)
    {
        size_t pos = str.find_first_of(":");
        return (pos != std::string::npos &&  pos != 0 && pos <= str.size());
    }

    auto HasNumberFormat(std::string_view str)
    {
        char c = '\0';
        bool result = false;
        for(auto& item : str)
        {
            if(numberFormatSet.contains(item))
            {
                result = true;
                c = item;
            }
        }
        return std::pair{result, c};
    }

    auto HasStringFormat(std::string_view str)
    {
        char c = '\0';
        bool result = false;
        for(auto& item : str)
        {
            if(stringFormatSet.contains(item))
            {
                result = true;
                c = item;
            }
        }
        return std::pair{result, c};
    }

    auto HasAlignment(std::string_view str)
    {
        std::string c = "";
        bool result = false;
        for(auto& item : alignmentSet)
        {
            if(str.find(item) != std::string::npos)
            {
                result = true;
                c = item;
            }
        }

        size_t alignmentNum = 0;
        if(size_t pos = str.find(c) + c.length(); pos < str.size() && pos != std::string::npos && pos != 0)
        {
            std::string s(str.substr(pos, str.end() - str.begin() - pos));
            alignmentNum = std::stoll(s);
        }


        return std::pair{result, std::pair{c, alignmentNum}};
    }

    auto HasPrecision(const std::string& str)
    {
        for(auto& item : precisionSet)
        {
            if(size_t pos = str.find(item); pos != std::string::npos)
            {
                return std::pair<bool, size_t>{true, std::stoll(str.substr(pos + 1, str.find_last_of("0123456789") - pos))};
            }
        }

        return std::pair<bool, size_t>{false, 0};
    }

    auto HasTimeFormat(std::string_view str)
    {
        char c = '\0';
        bool result = false;
        for(auto& item : str)
        {
            if(timeFormatSet.contains(item))
            {
                result = true;
                c = item;
            }
        }
        return std::pair{result, c};
    }

    bool IsArgFloating(std::string_view str)
    {
        return str.find(".") != std::string::npos;
    }

    auto GetIndexAndModifier(const std::string& str, size_t& count, bool& specifierUsed)
    {
        bool specifier = HasSpecifier(str);
        bool alignment = HasAlignment(str).first;
        bool precision = HasPrecision(str).first;

        if(!specifier && specifierUsed)
            throw std::runtime_error("Invalid format string");

        if(!specifier && (alignment || precision))
            return count++;

        if(!specifier && !alignment && !precision)
            return count++;

        if(specifier && !alignment && !precision)
            return count++;

        if(specifier && alignment && !precision)
            return count++;

        if(specifier && !alignment && precision)
            return count++;

        specifierUsed = true;

        size_t pos = str.find_first_of("0123456789");
        return size_t(std::stoll(str.substr(pos, str.find_first_of(":") - pos)));
    }

    void ProccessPrecision(size_t precision, std::string& arg, bool floating)
    {
        std::stringstream ss;
        if(floating)
            ss << std::setprecision(precision) << std::fixed << std::stod(arg);
        else
            ss << std::right << std::setw(precision) << std::setfill('0') << arg;
        arg = ss.str();
    }

    void ProcessAlignment(std::string& arg, std::pair<std::string, size_t> alignment)
    {
        std::stringstream ss;
        if(alignment.first == "<")
        {
            //center left
            ss << std::left << std::setw(alignment.second) << std::setfill(' ') << arg;
        }
        else if(alignment.first == "^<")
        {
            //center between fill
            size_t fill = alignment.second - arg.size();
            size_t fillLeft = fill / 2;
            size_t fillRight = fill - fillLeft;
            ss << std::left << std::setw(fillLeft) << std::setfill(' ') << "" << arg << std::setw(fillRight) << std::setfill(' ') << "";
        }
        else if(alignment.first == ">")
        {
            //center right
            ss << std::setw(alignment.second) << std::setfill(' ') << arg;
        }
        arg = ss.str();
    }

    void ProccesAligPrec(std::string& arg, const std::string& fmt, bool floating, bool proccessPrec, bool proccessAlign)
    {
        auto [hasPrecision, precision] = HasPrecision(fmt);
        auto [hasAlignment, alignment] = HasAlignment(fmt);

        if(hasPrecision && proccessPrec)
            ProccessPrecision(precision, arg, floating);

        if(hasAlignment && proccessAlign)
            ProcessAlignment(arg, alignment);
    }

    std::string DecToScientific(long long num, size_t precision)
    {
        auto exponent = (int)::log10(::fabs((double)num));

        // Berechnung der Mantisse
        double mantissa = (double)num / ::pow(10, exponent);

        std::stringstream ss;
        if(precision != 0)
            ss << std::setprecision(precision) << std::fixed << mantissa;
        else
            ss <<  std::setprecision(6) << std::fixed << mantissa;

        if(exponent <= 9)
            ss << "e+0" << exponent;
        else
            ss << "e+" << exponent;
        std::string result = ss.str();
        return ss.str();
    }

    void ProccessNumberFormat(std::string& arg, const std::string& fmt, char c)
    {
        bool floating = false;
        std::stringstream ss;
        bool precisionDone = false;

        switch(c)
        {
            case 'd':
            {
                ss << arg;
                break;
            }
            case 'x':
            {   
                if(IsArgFloating(arg))
                    ss << std::hexfloat << std::stold(arg);
                else
                    ss << std::hex << std::stoll(arg);
                break;
            }
            case 'X':
            {   
                if(IsArgFloating(arg))
                    ss << std::uppercase << std::hexfloat << std::stold(arg);
                else
                    ss << std::uppercase << std::hex << std::stoll(arg);
                break;
            }
            case 'o':
            {
                if(IsArgFloating(arg))
                    ss << decimalToOctal(std::stold(arg), 7);
                else
                    ss << std::oct << std::stoll(arg);
            }
            case 'b':
            {
                if(IsArgFloating(arg))
                    ss << std::bitset<sizeof(arg) * 8>(std::stold(arg));
                else
                    ss << std::bitset<sizeof(arg) * 8>(std::stoll(arg));
                break;
            }
            case 'e':
            {
                auto [hasPrecision, precision] = HasPrecision(fmt);

                if(IsArgFloating(arg))
                {
                    if(hasPrecision)
                    {
                        ss << std::scientific << std::setprecision(precision) << std::stold(arg);
                        precisionDone = true;
                    }
                    else
                        ss << std::scientific << std::stold(arg);
                }
                else
                {
                    if(hasPrecision)
                    {
                        ss << DecToScientific(std::stoll(arg), precision);
                        precisionDone = true;
                    }
                    else
                        ss << DecToScientific(std::stoll(arg), 0);
                }
                break;
            }
            case 'E':
            {
                auto [hasPrecision, precision] = HasPrecision(fmt);

                if(IsArgFloating(arg))
                {
                    if(hasPrecision)
                    {
                        ss << std::uppercase << std::scientific << std::setprecision(precision) << std::stold(arg);
                        precisionDone = true;
                    }
                    else
                        ss << std::uppercase << std::scientific << std::stold(arg);
                }
                else
                {
                    if(hasPrecision)
                    {
                        ss << std::uppercase << DecToScientific(std::stoll(arg), precision);
                        precisionDone = true;
                    }
                    else
                        ss << std::uppercase << DecToScientific(std::stoll(arg), 0);
                }
            }
            case 'f':
            {
                floating = true;
                ss << std::fixed << std::stold(arg);
                break;
            }
            case 'g':
            {
                if(IsArgFloating(arg))
                {
                    floating = true;
                    ss << std::defaultfloat << std::stold(arg);
                }
                else
                    ss << std::defaultfloat << std::stoll(arg);
                break;
            }
            case 'G':
            {
                if(IsArgFloating(arg))
                {
                    floating = true;
                    ss << std::defaultfloat << std::stold(arg);
                }
                else
                    ss << std::defaultfloat << std::stoll(arg);
                break;
            }
            case 'n':
            {
                ss.imbue(std::locale(ss.getloc(), new space_out));
                if(IsArgFloating(arg))
                    ss << std::stold(arg);
                else
                    ss << std::stoll(arg);
                break;
            }
            default:
                throw std::runtime_error("Invalid number format");
        }
        arg = ss.str();
        ProccesAligPrec(arg, fmt, floating, !precisionDone, true);
    }

    template <typename... T>
    std::string format(const std::string& fmt, T&&... args)
    {
        std::string result = fmt;

        auto posBegins = findPositions(fmt, "{");
        auto posEnds = findPositions(fmt, "}");
        if(posBegins.size() != posEnds.size())
            throw std::runtime_error("Invalid format string");

        std::vector<std::string> fmts;
        fmts.reserve(posBegins.size());
        for(size_t i = 0; i < posBegins.size(); ++i)
            fmts.emplace_back(fmt.substr(posBegins[i], posEnds[i] - posBegins[i] + 1));

        std::vector<std::string> argsStr;
        size_t countArgs = 0;
        (containerAndArgToString(argsStr, countArgs, args), ...);

        size_t count = 0;
        bool specifierUsed = false;
        for(auto const& item : fmts)
        {
            auto posItem = result.find(item);
            if(posItem == std::string::npos)
                throw std::runtime_error("Invalid format string");

            auto sizeItem = item.size();

            if(item == "{}" || item == "{:}") // empty braces && empty braces specifier
                result.replace(posItem, sizeItem, argsStr[count++]);
            else
            {
                auto indexPos = GetIndexAndModifier(item, count, specifierUsed);
                if(indexPos >= argsStr.size())
                    throw std::runtime_error("Index out of range");

                auto arg = argsStr[indexPos];
                auto [hasNumberFormat, numberFormat] = HasNumberFormat(item);
                auto [hasStringFormat, stringFormat] = HasStringFormat(item);
                auto [hasTimeFormat, timeFormat] = HasTimeFormat(item);

                if(hasNumberFormat)
                    ProccessNumberFormat(arg, item, numberFormat);
                else
                {
                    bool floating = arg.find(".") != std::string::npos;
                    ProccesAligPrec(arg, item, floating, true, true);
                }

                result.replace(posItem, sizeItem, arg);
            }
        }
        return result;
    }
}
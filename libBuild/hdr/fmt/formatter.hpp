#pragma once
#include <sstream>
#include <string>
#include <ostream>

namespace elog::formatMap
{
    template<typename T>
    struct Formatter
    {
        static std::string format(const T& value)
        {
            std::ostringstream ss;
            ss << value;
            return std::move(ss.str());
        }
    };

    template<typename T>
    struct Formatter<std::vector<T>>
    {
        static std::string format(const std::vector<T>& value)
        {
            std::ostringstream ss;
            ss << "[";
            for (auto& item : value)
            {
                ss << Formatter<T>::format(item) << ", ";
            }
            ss << "]";
            return std::move(ss.str());
        }
    };

    template<typename T, typename U>
    struct Formatter<std::pair<T, U>>
    {
        static std::string format(const std::pair<T, U>& value)
        {
            std::ostringstream ss;
            ss << "(" << Formatter<T>::format(value.first) << ", " << Formatter<U>::format(value.second) << ")";
            return std::move(ss.str());
        }
    };

    template<typename T, typename U>
    struct Formatter<std::unordered_map<T, U>>
    {
        static std::string format(const std::unordered_map<T, U>& value)
        {
            std::ostringstream ss;
            ss << "{";
            for (auto& item : value)
            {
                ss << Formatter<std::pair<T, U>>(item) << ", ";
            }
            ss << "}";
            return std::move(ss.str());
        }
    };

}


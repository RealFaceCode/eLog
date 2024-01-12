#pragma once
#include <sstream>
#include <string>
#include <ostream>
#include <unordered_map>
#include <vector>

namespace elog::fmt
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
            std::stringbuf buf;
            buf.sputc('[');
            std::string str;
            for (auto& item : value)
            {
                if(&item == &value.back())
                    str = Formatter<T>::format(item);
                else
                    str = Formatter<T>::format(item) + ", ";
                buf.sputn(str.c_str(), str.size());
            }
            buf.sputc(']');
            return std::move(buf.str());
        }
    };
    template<typename T, typename U>
    struct Formatter<std::pair<T, U>>
    {
        static std::string format(const std::pair<T, U>& value)
        {
            std::stringbuf buf;
            buf.sputn("[First: ", 8);
            auto str = Formatter<T>::format(value.first);
            buf.sputn(str.c_str(), str.size());
            buf.sputn(", Second: ", 10);
            str = Formatter<U>::format(value.second);
            buf.sputn(str.c_str(), str.size());
            buf.sputc(']');
            return std::move(buf.str());
        }
    };

    template<typename T, typename U>
    struct Formatter<std::unordered_map<T, U>>
    {
        static std::string format(const std::unordered_map<T, U>& value)
        {
            std::stringbuf buf;
            buf.sputc('{');
            std::string str;
            for (auto& item : value)
                str = Formatter<std::pair<T, U>>::format(item);
            buf.sputc('}');
            return std::move(buf.str());
        }
    };
}


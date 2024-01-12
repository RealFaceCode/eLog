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

        static void format_to(std::stringbuf& buf, const T& value)
        {
            std::ostringstream ss;
            ss << value;
            buf.sputn(ss.str().c_str(), ss.str().size());
        }
    };

    template<>
    struct Formatter<std::stringbuf>
    {
        static std::string format(const std::stringbuf& value)
        {
            return std::move(value.str());
        }

        static void format_to(std::stringbuf& buf, const std::stringbuf& value)
        {
            auto str = value.view();
            buf.sputn(str.data(), str.size());
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

        static void format_to(std::stringbuf& buf, const std::vector<T>& value)
        {
            buf.sputc('[');
            for (auto& item : value)
            {
                if(&item == &value.back())
                    Formatter<T>::format_to(buf, item);
                else
                {
                    Formatter<T>::format_to(buf, item);
                    buf.sputn(", ", 2);
                }
                
            }
            buf.sputc(']');
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

        static void format_to(std::stringbuf& buf, const std::pair<T, U>& value)
        {
            buf.sputn("[First: ", 8);
            Formatter<T>::format_to(buf, value.first);
            buf.sputn(", Second: ", 10);
            Formatter<U>::format_to(buf, value.second);
            buf.sputc(']');
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

        static void format_to(std::stringbuf& buf, const std::unordered_map<T, U>& value)
        {
            buf.sputc('{');
            for (auto& item : value)
            {
                Formatter<std::pair<T, U>>::format_to(buf, item);
                buf.sputn(", ", 2);
            }
            buf.sputc('}');
        }
    };
}


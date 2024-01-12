#pragma once

#include "checks.hpp"
#include "argument.hpp"
#include "exceptions.hpp"

#include <cstring>

namespace elog::fmt
{
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

    template<typename... Args>
    inline ArgParser::ArgParser(Args&& ...args)
    {
        parseArgs(args...);
    }

    inline std::vector<Argument>& ArgParser::getArgList()
    {
        return mArguments;
    }

    template <typename Arg>
    inline void ArgParser::argToString(std::stringbuf& buf, Argument& argument, Arg& arg)
    {
        std::stringstream ss;
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
            ss << arg;
            auto view = ss.view();
            buf.sputn(view.data(), view.size());
        }
        else if constexpr (is_float_v<not_ref_type<Arg>>)
        {
            argument.setArgumentType(ArgumentType::Float);
            ss << arg;
            auto view = ss.view();
            buf.sputn(view.data(), view.size());
        }
        else if constexpr (is_double_v<not_ref_type<Arg>>)
        {
            argument.setArgumentType(ArgumentType::Double);
            ss << arg;
            auto view = ss.view();
            buf.sputn(view.data(), view.size());
        }
        else if constexpr (is_bool_v<not_ref_type<Arg>>)
        {
            argument.setArgumentType(ArgumentType::Bool);
            ss << arg;
            auto view = ss.view();
            buf.sputn(view.data(), view.size());
        }
        else if constexpr (is_pointer_v<not_ref_type<Arg>>)
        {
            argument.setArgumentType(ArgumentType::Pointer);
            ss << (uintptr_t)arg;
            auto view = ss.view();
            buf.sputn(view.data(), view.size());
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
                        buf.sputn(", ", 2);
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
    inline void ArgParser::parseArg(Arg& arg)
    {
        Argument argument;
        std::stringbuf buf;
        
        argToString(buf, argument, arg);

        argument.value = std::move(buf);
        mArguments.push_back(std::move(argument));
    }

    template<typename... Args>
    inline void ArgParser::parseArgs(Args&& ...args)
    {
        size_t numArgs = sizeof...(Args);
        if(numArgs == 0)
            return;

        mArguments.reserve(numArgs);

        (parseArg(args), ...);
    }
}
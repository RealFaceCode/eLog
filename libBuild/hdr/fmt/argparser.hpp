#pragma once

#include "checks.hpp"
#include "argument.hpp"
#include "exceptions.hpp"
#include "formatter.hpp"

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
        template<typename Arg>
        void parseArg(const Arg& arg);

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

    template<typename Arg>
    inline void ArgParser::parseArg(const Arg& arg)
    {
        Argument argument;
        Formatter<Arg>::format_to(argument.value, arg);
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
#pragma once

#include <sstream>

namespace elog::fmt
{
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
        Class
    };

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
        std::stringbuf value;
    };
}
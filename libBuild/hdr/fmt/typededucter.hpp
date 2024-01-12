#pragma once

#include "argument.hpp"
#include "checks.hpp"
#include "exceptions.hpp"

namespace elog::fmt
{
    template<typename T>
    struct TypeDeducter
    {
        static void deduct(ArgumentType& type)
        {
            if constexpr (is_string_type_v<T>)
                type = ArgumentType::String;
            else if constexpr (is_char_v<T>)
                type = ArgumentType::Char;
            else if constexpr (is_bool_v<T>)
                type = ArgumentType::Bool;
            else if constexpr (is_integer_v<T>)
                type = ArgumentType::Int;
            else if constexpr (is_float_v<T>)
                type = ArgumentType::Float;
            else if constexpr (is_double_v<T>)
                type = ArgumentType::Double;
            else if constexpr (is_pointer_v<T>)
                type = ArgumentType::Pointer;
            else if constexpr (is_container_v<T>)
                type = ArgumentType::Container;
            else
                throw TypeDeductionException("Type deduction failed!");
        }
    };
}
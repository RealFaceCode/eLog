#include "fmt/argument.hpp"

namespace elog::fmt
{
    void Argument::setArgumentType(ArgumentType type)
    {
        if(this->type == ArgumentType::None)
            this->type = type;
    }
}
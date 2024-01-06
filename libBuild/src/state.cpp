#include "state.hpp"

#include "logcolor.hpp"

namespace elog
{

    namespace exception
    {
        StateExeption::StateExeption(const char* msg)
        : msg(msg)
        {}

        StateExeption::StateExeption(const std::string& msg)
        : msg(msg)
        {}

        StateExeption::StateExeption(std::string_view msg)
        : msg(msg)
        {}

        const char* StateExeption::what() const noexcept
        {
            return msg.c_str();
        }
    }
    
    namespace structs
    {
        std::shared_ptr<State> state;
    }

    namespace internal
    {
        std::shared_ptr<structs::State> GetState()
        {
            if(!structs::state)
                throw exception::StateExeption("State is not initialized");
            return structs::state;
        }
    }

    void Init()
    {
        structs::state = std::make_shared<structs::State>();
        internal::SetColorToState();
    }

    void SetState(enums::StateFlag flag)
    {
        auto state = internal::GetState().get();

        switch (flag)
        {
        default:
            break;
        }
    }
}
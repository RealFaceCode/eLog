#include "state.hpp"

#include "logcolor.hpp"
#include "loglevel.hpp"

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

        bool IsFlagSet(enums::StateFlag flag)
        {
            auto state = internal::GetState().get();
            return state->flags & static_cast<unsigned int>(flag);
        }
    }

    void Init()
    {
        if(structs::state)
            return;
            
        structs::state = std::make_shared<structs::State>();
        structs::state->flags = static_cast<unsigned int>(enums::StateFlag::DEFAULT);

        internal::SetColorToState();
        internal::SetLogLevels();
    }

    void SetState(enums::StateFlag flags)
    {
        auto& state = *internal::GetState().get();
        state.flags = 0;
        
        state->flags |= static_cast<unsigned int>(flags);
    }

    void ToggleState(enums::StateFlag flag)
    {
        auto state = internal::GetState().get();
        state->flags ^= static_cast<unsigned int>(flag);
    }
}
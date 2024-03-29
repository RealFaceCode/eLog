#include "state.hpp"

#include "logcolor.hpp"
#include "loglevel.hpp"
#include "msg.hpp"
#include "thread.hpp"

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

        bool CheckFlagToEnum(enums::StateFlag flag, enums::StateFlag check)
        {
            return static_cast<unsigned int>(flag) & static_cast<unsigned int>(check);
        }

        const std::string& GetResetColor()
        {
            auto& state = *internal::GetState().get();
            return state.resetColor;
        }

        const std::string& GetTimeFormatStr()
        {
            auto& state = *internal::GetState().get();
            return state.timeFormat;
        }

        const std::string& GetDateFormatStr()
        {
            auto& state = *internal::GetState().get();
            return state.dateFormat;
        }
    }

    void Init()
    {
        if(structs::state)
            return;
            
        structs::state = std::make_shared<structs::State>();
        structs::state->flags = static_cast<unsigned int>(enums::StateFlag::DEFAULT);
        structs::state->resetColor = "\033[0m";
        structs::state->timeFormat = "%H:%M:%S";
        structs::state->dateFormat = "%Y-%m-%d";
        structs::state->queueThreadRunning = false;
        structs::state->isWaitingToClose = false;
        structs::state->logFilePath = "log.txt";

        internal::SetColorToState();
        internal::SetLogLevels();
    }

    void SetState(enums::StateFlag flags)
    {
        auto& state = *internal::GetState().get();
        state.flags = 0;
        
        state.flags |= static_cast<unsigned int>(flags);
    }

    bool CheckUp(enums::StateFlag flag)
    {
        return (internal::CheckFlagToEnum(flag, enums::StateFlag::CLR_ON) && internal::IsFlagSet(enums::StateFlag::CLR_ON)
            || internal::CheckFlagToEnum(flag, enums::StateFlag::CLR_OFF) && internal::IsFlagSet(enums::StateFlag::CLR_OFF)) 
            || (internal::CheckFlagToEnum(flag, enums::StateFlag::LOG_THREAD) && internal::IsFlagSet(enums::StateFlag::LOG_THREAD)
            || internal::CheckFlagToEnum(flag, enums::StateFlag::LOG_NORMAL) && internal::IsFlagSet(enums::StateFlag::LOG_NORMAL));
    }

    void ToggleState(enums::StateFlag flag)
    {
        auto& state = *internal::GetState().get();

        if(CheckUp(flag))
            return;
        
        if(static_cast<unsigned int>(flag) & (static_cast<unsigned int>(enums::StateFlag::RESET)))
        {
            state.flags = static_cast<unsigned int>(enums::StateFlag::DEFAULT);
            return;
        }
        else if(internal::CheckFlagToEnum(flag, enums::StateFlag::CLR_ON)
                && internal::IsFlagSet(enums::StateFlag::CLR_OFF))
            state.flags ^= static_cast<unsigned int>(enums::StateFlag::CLR_OFF);
        else if(internal::CheckFlagToEnum(flag, enums::StateFlag::CLR_OFF)
                && internal::IsFlagSet(enums::StateFlag::CLR_ON))
            state.flags ^= static_cast<unsigned int>(enums::StateFlag::CLR_ON);
        else if(internal::CheckFlagToEnum(flag, enums::StateFlag::LOG_THREAD)
                && internal::IsFlagSet(enums::StateFlag::LOG_NORMAL))
        {
            state.flags ^= static_cast<unsigned int>(enums::StateFlag::LOG_NORMAL);
            internal::StartThread();
        }
        else if(internal::CheckFlagToEnum(flag, enums::StateFlag::LOG_NORMAL)
                && internal::IsFlagSet(enums::StateFlag::LOG_THREAD))
        {
            state.flags ^= static_cast<unsigned int>(enums::StateFlag::LOG_THREAD);
            internal::StopThread();
        }

        state.flags ^= static_cast<unsigned int>(flag);
    }

    void SetTimeFormat(std::string_view format)
    {
        auto& state = *internal::GetState().get();
        state.timeFormat = format;
    }

    void SetDateFormat(std::string_view format)
    {
        auto& state = *internal::GetState().get();
        state.dateFormat = format;
    }
}
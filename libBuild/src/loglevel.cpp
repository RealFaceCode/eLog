#include "loglevel.hpp"
#include "state.hpp"
#include "logcolor.hpp"

namespace elog
{
    namespace internal
    {
        void SetLogLevels()
        {
            auto& state = *GetState().get();
            state.logLevels["TRACE"] = {enums::Color::Gray, {}};
            state.logLevels["DEBUG"] = {enums::Color::Blue, {}};
            state.logLevels["INFO"] = {enums::Color::White, {}};
            state.logLevels["WARNING"] = {enums::Color::Yellow, {}};
            state.logLevels["ERROR"] = {enums::Color::Red, {}};
            state.logLevels["FATAL"] = {enums::Color::Magenta, {}};
        }

        std::optional<std::reference_wrapper<structs::LogColor>> GetLogColor(std::string_view logLevel)
        {
            auto& state = *GetState().get();
            auto it = state.logLevels.find(std::string(logLevel));
            if(it != state.logLevels.end())
                return it->second;
            return {};
        }
    }

    void AddLogLevel(std::string_view logLevel, enums::Color color, const std::vector<enums::Effect>& effect)
    {
        auto& state = *internal::GetState().get();
        state.logLevels.insert({std::string(logLevel), {color, effect}});
    }

    void ChangeLogLevelColor(std::string_view logLevel, enums::Color color)
    {
        auto option = internal::GetLogColor(logLevel);
        if(option.has_value())
            option.value().get().color = color;
    }

    void ChangeLogLevelEffect(std::string_view logLevel, const std::vector<enums::Effect>& effect)
    {
        auto option = internal::GetLogColor(logLevel);
        if(option.has_value())
            option.value().get().effect = effect;
    }

    void RemoveLogLevel(std::string_view logLevel)
    {
        auto& state = *internal::GetState().get();
        state.logLevels.erase(std::string(logLevel));
    }
}
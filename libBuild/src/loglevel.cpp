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
            state.logLevels["CRITICAL"] = {enums::Color::Magenta, {}};
        }

        std::optional<const structs::LogColor&> GetLogColor(std::string_view logLevel)
        {
            auto& state = *GetState().get();
            auto it = state.logLevels.find(std::string(logLevel));
            if(it == state.logLevels.end())
                return std::nullopt;
            return it->second;
        }
    }

    void AddLogLevel(std::string_view logLevel, enums::Color color, const std::vector<enums::Effect>& effect)
    {
        auto& state = *internal::GetState().get();

        structs::LogColor ll = {color, {}};
        for(auto& e : effect)
            ll.effect.insert(e);

        state.logLevels.insert({std::string(logLevel), ll});
    }
}
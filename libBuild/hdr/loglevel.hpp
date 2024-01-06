#pragma once

#include <string_view>
#include <vector>
#include <set>
#include <optional>

namespace elog
{   
    namespace enums
    {
        enum class Color;
        enum class Effect;
    }

    namespace structs
    {
        struct LogColor
        {
        public:
            enums::Color color;
            std::set<enums::Effect> effect;
        };
    }

    namespace internal
    {
        void SetLogLevels();
        std::optional<const structs::LogColor&> GetLogColor(std::string_view logLevel);
    }

    void AddLogLevel(std::string_view logLevel, enums::Color color, const std::vector<enums::Effect>& effect = {});
}
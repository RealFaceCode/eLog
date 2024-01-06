#pragma once

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>

namespace elog
{
    namespace exception
    {
        struct StateExeption : public std::exception
        {
        public:
            StateExeption() = default;
            StateExeption(const char* msg);
            StateExeption(const std::string& msg);
            StateExeption(std::string_view msg );
            ~StateExeption() = default;

            StateExeption(const StateExeption&) = default;
            StateExeption& operator=(const StateExeption&) = default;
            StateExeption(StateExeption&&) = default;
            StateExeption& operator=(StateExeption&&) = default;

            const char* what() const noexcept override;

        private:
            std::string msg = "";
        };
    }

    namespace enums
    {
        enum class StateFlag
        {

        };

        enum class Color;
        enum class Effect;
    }

    namespace structs
    {
        struct State
        {   
            std::unordered_map<std::string, std::string> logLevels;
            std::unordered_map<enums::Color, std::string> logColors;
            std::unordered_map<enums::Effect, std::string> logEffects;
        };
    }

    namespace internal
    {
        std::shared_ptr<structs::State> GetState();
    }

    void Init();
    void SetState(enums::StateFlag flag);
}
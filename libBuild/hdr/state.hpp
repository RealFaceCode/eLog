#pragma once

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <string_view>
#include <queue>
#include <exception>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <fstream>

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
        enum class StateFlag : unsigned int
        {
            RESET = 0,
            FMT_TIME = 1 << 0,
            FMT_DATE = 1 << 1,
            FMT_FUNCTION = 1 << 2,
            FMT_FILE = 1 << 3,
            FMT_LINE = 1 << 4,
            LOG_NORMAL = 1 << 5,
            LOG_THREAD = 1 << 6,
            LOG_THREAD_WAIT = 1 << 7,
            CLR_ON = 1 << 8,
            CLR_OFF = 1 << 9,
            OUT_TERMINAL = 1 << 10,
            OUT_FILE = 1 << 11,
            OUT_BUFFER = 1 << 12,
            OUT_NETWORK = 1 << 13,

            DEFAULT = OUT_TERMINAL | FMT_TIME | FMT_DATE | FMT_FUNCTION | FMT_FILE | FMT_LINE | LOG_NORMAL | CLR_ON,
        };

        enum class Color;
        enum class Effect;
    }

    namespace structs
    {
        struct LogColor;
        template<typename ...Args>
        struct Msg;

        struct State
        {
            std::unordered_map<std::string, LogColor> logLevels;
            std::unordered_map<enums::Color, std::string> logColors;
            std::unordered_map<enums::Effect, std::string> logEffects;
            std::queue<Msg<>> msgQueue;
            std::vector<std::stringbuf> logBuffer;
            unsigned int flags;
            std::string resetColor;
            std::string timeFormat;
            std::string dateFormat;
            std::mutex queueMutex;
            std::condition_variable queueCv;
            std::jthread queueThread;
            bool queueThreadRunning;
            bool isWaitingToClose;
            std::ofstream logFile;
            std::string logFilePath;
        };
    }

    namespace internal
    {
        std::shared_ptr<structs::State> GetState();
        bool IsFlagSet(enums::StateFlag flag);
        const std::string& GetResetColor();
        const std::string& GetTimeFormat();
        const std::string& GetDateFormat();
    }

    void Init();
    void SetState(enums::StateFlag flags);
    void ToggleState(enums::StateFlag flag);
    void SetTimeFormat(std::string_view format);
    void SetDateFormat(std::string_view format);
}
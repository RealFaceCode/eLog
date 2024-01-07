#pragma once

#include <thread>
#include <queue>
#include <condition_variable>

namespace elog
{

    namespace structs
    {
        template<typename... Args>
        struct Msg;
    }

    namespace internal
    {
        std::condition_variable& GetCv();
        std::mutex& GetMutex();
        std::jthread& GetThread();
        bool& GetIsRunning();
        bool& GetIsWaiting();
        std::queue<structs::Msg<>>& GetQueue();
        void Worker(std::stop_token stopToken);
        void AddTask(structs::Msg<>&& msg);
    }

    void StartThread();
    void StopThread(bool wait = true);
}
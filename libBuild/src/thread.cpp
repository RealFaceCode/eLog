#include "thread.hpp"

#include <mutex>

#include "state.hpp"
#include "msg.hpp"
#include "elog.hpp"

namespace elog::internal
{
    std::condition_variable& GetCv()
    {
        auto& state = *internal::GetState();
        return state.queueCv;
    }

    std::mutex& GetMutex()
    {
        auto& state = *internal::GetState();
        return state.queueMutex;
    }

    std::jthread& GetThread()
    {
        auto& state = *internal::GetState();
        return state.queueThread;
    }

    bool& IsRunning()
    {
        auto& state = *internal::GetState();
        return state.queueThreadRunning;
    }

    bool& IsWaiting()
    {
        auto& state = *internal::GetState();
        return state.isWaitingToClose;
    }

    std::queue<structs::Msg<>>& GetQueue()
    {
        auto& state = *internal::GetState();
        return state.msgQueue;
    }

    void Worker(std::stop_token stopToken)
    {
        while(!stopToken.stop_requested())
        {
            std::unique_lock lock(GetMutex());
            auto& queue = GetQueue();
            GetCv().wait(lock, [&queue]{ return !queue.empty() && IsRunning() || IsWaiting(); });
            
            if(queue.empty())
                continue;

            auto msg = std::move(queue.front());
            queue.pop();
            lock.unlock();

            internal::logOut(std::move(msg));
        }
    }

    void AddTask(structs::Msg<>&& msg)
    {
        std::unique_lock lock(GetMutex());
        auto& state = *internal::GetState();
        state.msgQueue.push(std::move(msg));
        internal::GetCv().notify_one();
    }

    void StartThread()
    {
        if(internal::IsRunning())
            return;

        auto& state = *internal::GetState();
        state.queueThreadRunning = true;
        state.queueThread = std::jthread(internal::Worker);
    }

    void StopThread()
    {
        if(!internal::IsRunning())
            return;

        auto& state = *internal::GetState();
        if(internal::IsFlagSet(enums::StateFlag::LOG_THREAD_WAIT))
        {
            state.isWaitingToClose = true;
            while(!state.msgQueue.empty())
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        state.queueThreadRunning = false;
        state.queueThread.request_stop();
        internal::GetCv().notify_one();
        internal::GetThread().join();
        state.isWaitingToClose = false;
    }

}
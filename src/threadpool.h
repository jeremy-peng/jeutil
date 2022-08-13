#pragma once

#include <queue>
#include <mutex>
#include <functional>
#include <condition_variable>
#include <thread>

namespace tpool
{

    class ThreadPool
    {

    public:
        ThreadPool(int numThreads);
        virtual ~ThreadPool();

        template <typename... ARGS>
        void addTask(std::function<void(ARGS...)> func, ARGS... args)
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_taskQueue.emplace(std::bind(func, args...));
            lock.unlock();
            m_cv.notify_one();
        }

        void stop();

    private:
        void worker_loop();

    private:
        std::mutex m_mutex;
        std::queue<std::function<void()>> m_taskQueue;
        std::condition_variable m_cv;
        std::vector<std::thread> m_threads;
        bool m_isStopping = false;
    };

}

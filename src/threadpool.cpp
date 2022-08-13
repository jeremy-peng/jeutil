#include "threadpool.h"
#include <iostream>

namespace tpool
{

    ThreadPool::ThreadPool(int numThreads)
    {
        m_threads.reserve(numThreads);
        for (int i = 0; i < numThreads; i++)
        {
            m_threads.emplace_back(std::thread(&ThreadPool::worker_loop, this));
        }
    }

    ThreadPool::~ThreadPool()
    {
        stop();
    }

    void ThreadPool::worker_loop()
    {
        while (1)
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_cv.wait(lock, [this]
                      { return m_isStopping || m_taskQueue.size() > 0; });
            if (m_isStopping)
                return;
            auto func = std::move(m_taskQueue.front());
            m_taskQueue.pop();
            lock.unlock();
            func();
        }
    }

    void ThreadPool::stop()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_isStopping = true;
        lock.unlock();
        m_cv.notify_all();

        for (int i = 0; i < m_threads.size(); i++)
        {
            std::cout << "joining thread " << i << std::endl;
            m_threads[i].join();
        }
        m_threads.clear();
    }

} // namespace tpool

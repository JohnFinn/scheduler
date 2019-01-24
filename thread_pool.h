#pragma once

#include <functional>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>

// finishes all tasks in destructor
class ThreadPool {
    std::vector<std::thread> workers;
    std::queue<std::function<void(void)>> tasks;
    bool running = true;
    std::mutex tasks_lock;
    std::condition_variable continue_condition;
public:
    ThreadPool(size_t n_thread) noexcept;
    ~ThreadPool() noexcept;
    void push(std::function<void(void)> func) noexcept;
private:
    void run() noexcept;

    // not sure what the expected results are
    ThreadPool(const ThreadPool& other) noexcept;
    ThreadPool(ThreadPool&& other) noexcept;
    void operator=(const ThreadPool& other) noexcept;
    void operator=(ThreadPool&& other) noexcept;
};

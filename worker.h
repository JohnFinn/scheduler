#pragma once

#include <functional>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

// finishes all tasks in destructor
class Worker{
    std::thread worker_thread;
    std::queue<std::function<void(void)>> tasks;
    bool running = true;
    std::mutex tasks_lock;
    std::condition_variable continue_condition;
public:
    Worker() noexcept;
    ~Worker() noexcept;
    void push(std::function<void(void)> func) noexcept;
private:
    void run() noexcept;

    // not sure what the expected results are
    Worker(const Worker& other) noexcept;
    Worker(Worker&& other) noexcept;
    void operator=(const Worker& other) noexcept;
    void operator=(Worker&& other) noexcept;
};

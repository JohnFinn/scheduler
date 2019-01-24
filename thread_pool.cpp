#include "thread_pool.h"

ThreadPool::ThreadPool(size_t n_thread) noexcept : workers(n_thread) {
    for (auto& worker : this->workers)
        worker = std::thread(&ThreadPool::run, this);
}

ThreadPool::~ThreadPool() noexcept {
    this->tasks_lock.lock();
    this->running = false;
    this->continue_condition.notify_all();
    this->tasks_lock.unlock();
    for (auto& worker : this->workers)
        worker.join();
}

void ThreadPool::push(std::function<void(void)> func) noexcept {
    std::lock_guard lg(this->tasks_lock);
    this->tasks.emplace(func);
    this->continue_condition.notify_all();
}

void ThreadPool::run() noexcept {
    std::unique_lock ul(this->tasks_lock);
    while (this->running or this->tasks.size() > 0) {
        while (this->running and this->tasks.size() == 0) {
            this->continue_condition.wait(ul);
        }
        while (this->tasks.size() > 0){
            auto func = this->tasks.front();
            tasks.pop();
            ul.unlock();
            func();
            ul.lock();
        }
    }
}

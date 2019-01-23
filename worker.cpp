#include "worker.h"

Worker::Worker() noexcept {
    worker_thread = std::thread(&Worker::run, this);
}

Worker::~Worker() noexcept {
    this->tasks_lock.lock();
    this->running = false;
    this->continue_condition.notify_one();
    this->tasks_lock.unlock();
    this->worker_thread.join();
}

void Worker::push(std::function<void(void)> func) noexcept {
    std::lock_guard lg(this->tasks_lock);
    this->tasks.emplace(func);
    this->continue_condition.notify_one();
}

void Worker::run() noexcept {
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

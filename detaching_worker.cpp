#include "detaching_worker.h"

DetachingWorker::DetachingWorker() noexcept {
    this->thread = std::thread(&DetachingWorker::run, this);
    this->thread.detach();
    while (this->worker_ptr == nullptr)
        ;
}

void DetachingWorker::run() noexcept {
    Worker worker;
    this->worker_ptr = &worker;
}

void DetachingWorker::push(std::function<void(void)> func) noexcept {
    this->worker_ptr->push(func);
}

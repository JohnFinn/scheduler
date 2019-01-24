#pragma once
#include <worker.h>

class DetachingWorker {
    std::thread thread;
    Worker* worker_ptr = nullptr;
public:
    DetachingWorker() noexcept;
    void push(std::function<void(void)> func) noexcept;
private:
    void run() noexcept;

    // not sure what the expected results are
    DetachingWorker(const DetachingWorker& other) noexcept;
    DetachingWorker(DetachingWorker&& other) noexcept;
    void operator=(const Worker& other) noexcept;
    void operator=(Worker&& other) noexcept;
};

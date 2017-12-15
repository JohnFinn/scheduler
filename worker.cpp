#ifndef WORKER_CPP
#define WORKER_CPP

#include <functional>
#include <thread>
#include <queue>
#include <condition_variable>

namespace worker {
	using namespace std;

template <class type>
class Worker : public thread {
private:
	function<void(type)> process;
	bool paused;
	bool quit;
	bool running;
	queue<type> tasks;
	condition_variable cond;
	mutex mu_tasks;
	// mutex mu_flags;
public:

	Worker(function<void(type)>&  func) : running(true), quit(false), paused(false),
	thread(&Worker::run, this), process(func) {}
	Worker(function<void(type)>&& func) : running(true), quit(false), paused(false),
	thread(&Worker::run, this), process(move(func)) {}

	void push(type number) noexcept {
		unique_lock<mutex> ul(mu_tasks);
		tasks.push(number);
		cond.notify_one();
	}


	// sometimes deadlock or segfault
	void run(){
		unique_lock<mutex> ul(mu_tasks);
		while (running) {
			cond.wait(ul, [&](){ return !running or (!paused and !tasks.empty()); });
			if (!running) // if tasks are empty, we won't process anything
				break;
			type task = tasks.front();
			tasks.pop();
			process(task);
		}
		if (quit)
			while (!tasks.empty()){
				process(tasks.front());
				tasks.pop();
			}
}
	// process all remained tasks
	void join() noexcept {
		quit = true;
		stop();
		thread::join();
	}
	// stop aftre processing last task
	// breaks out of while loop in Worker::run
	void stop() noexcept {
		running = false;
		unique_lock<mutex> ul(mu_tasks);
		cond.notify_one();
	}

	void pause() noexcept {
		paused = true;
	}

	void resume() noexcept {
		if (paused){
			paused = false;
			cond.notify_one();
		}
	}
};

} // namespace worker
using worker::Worker;
#endif
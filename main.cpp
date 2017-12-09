#include "/home/jouny/Documents/oop/prime_factorizator/pf.h"
#include <string>
#include <exception>
#include <iostream>
#include <queue>
#include <thread>
#include <condition_variable>
#include <functional>

using namespace std;

unsigned long stoint(const string& s){
	unsigned long result = 0;
	for (auto i : s){
		if (not (i >= '0' and i <= '9') )
			throw invalid_argument(s + " is not a number");
		result *= 10;
		result += i - '0';
	}
	return result;
}

template <class type>
class Calculator : public thread{
public:
	function<void(type)> process;
	bool running;
	bool paused;
	bool quit;
	queue<type> tasks;
	condition_variable cond;
	mutex mu_tasks;
public:

	Calculator(function<void(type)> func) : thread(&Calculator::run, this) {
		process = func;
	}

	void push(type number) noexcept {
		unique_lock<mutex> ul(mu_tasks);
		tasks.push(number);
		ul.unlock();
		cond.notify_one();
	}

	void run(){
		running = true;
		quit = paused = false;
		while (running) {
			unique_lock<mutex> ul(mu_tasks);
			cond.wait(ul, [&](){ return quit or (!paused and (!tasks.empty() or !running)); });
			if (tasks.empty())
				break;

			if (quit){
				while (!tasks.empty()){
					process(tasks.front());
					tasks.pop();
				}
				break;
			}

			process(tasks.front());

			tasks.pop();
		}
	}

	void join(){
		quit = true;
		cond.notify_one();
		thread::join();
	}

	void stop() noexcept {
		running = false;
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


int main(int argc, char const *argv[]){
	Calculator<unsigned long int> calc([&](unsigned long int i){ cout << PFact(i) << '\n'; });

	unsigned int number = 0;
	for (string line; getline(cin, line, '\n');){
		if (line == "exit"){
			calc.stop();
			break;
		} else if (line == "pause"){
			calc.pause();
			continue;
		} else if (line == "resume"){
			calc.resume();
			continue;
		}

		try{
			number = stoint(line);
		} catch (invalid_argument ex){
			cerr << ex.what() << '\n';
			continue;
		}
		calc.push(number);
	}

	// need to wait for else's
	// calc.wait();
	calc.join();

	return 0;
}

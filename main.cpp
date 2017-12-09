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
	function<void(type)> process;
	bool running;
	bool paused;
	queue<type> numbers;
	condition_variable cond;
	mutex mu_numbers;
public:

	Calculator(function<void(type)> func) : thread(&Calculator::run, this) {
		process = func;
	}

	void push(type number){
		unique_lock<mutex> ul(mu_numbers);
		numbers.push(number);
		ul.unlock();
		cond.notify_one();
	}

	void run(){
		running = true;
		paused = false;
		while (running) {
			unique_lock<mutex> ul(mu_numbers);
			cond.wait(ul, [&](){ return !paused and (!numbers.empty() or !running); });
			if (numbers.empty())
				break;

			// cout << PFact(numbers.front()) << '\n';
			process(numbers.front());

			numbers.pop();
		}
	}

	void stop(){
		running = false;
		cond.notify_one();
	}

	void pause(){
		paused = true;
	}

	void resume(){
		paused = false;
		cond.notify_one();
	}
};


int main(int argc, char const *argv[]){
	Calculator<unsigned long int> calc([&](unsigned long int i){ cout << PFact(i) << '\n'; });

	unsigned int number = 0;
	for (string line; getline(cin, line);){
		if (line == "exit")
			break;
		else if (line == "pause"){
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

	calc.stop();
	calc.join();

	return 0;
}
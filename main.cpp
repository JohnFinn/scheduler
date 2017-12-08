#include "/home/jouny/Documents/oop/prime_factorizator/pf.h"
#include <string>
#include <exception>
#include <iostream>
#include <queue>
#include <thread>

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


class Calculator : public thread{
	using thread::thread;
	bool running;
	queue<unsigned long int> numbers;
public:

	Calculator() : thread(&Calculator::run, this) {}

	void push(unsigned long int number){
		numbers.push(number);
	}

	void run(){
		running = true;
		while (running) {
			if (!numbers.empty()){
				cout << PFact(numbers.front()) << '\n';
				numbers.pop();
			}
		}
	}

	void stop(){
		running = false;
		while (!numbers.empty())
			numbers.pop();
	}
};


int main(int argc, char const *argv[]){
	Calculator calc;

	unsigned int number = 0;
	for (string line; getline(cin, line);){
		if (line == "exit"){
			calc.stop();
			break;
		}
		try{
			number = stoint(line);
		} catch (invalid_argument ex){
			cerr << ex.what() << '\n';
			continue;
		}
		calc.push(number);
	}

	calc.join();

	return 0;
}
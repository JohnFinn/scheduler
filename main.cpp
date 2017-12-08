#include "scheduler.h"
#include "/home/jouny/Documents/oop/prime_factorizator/pf.h"
#include <string>
#include <exception>
#include <iostream>

using namespace std;

template <class ...args>
void func(args...){

}

template <class ...args>
void call(args...){
	// func(args...);
}

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

int main(int argc, char const *argv[]){
	Scheduler sched;

	// call(0,1,2);

    for (string line; getline(cin, line);){
		try{
			unsigned int number = stoint(line);
		} catch (invalid_argument ex){
			cerr << ex.what() << '\n';
			continue;
		}
		// sched.addtask
		cout << PFact(stoint(line)) << '\n';
    }
	return 0;
}
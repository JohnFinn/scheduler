#include "/home/jouny/Documents/oop/prime_factorizator/pf.h"
#include <string>
#include <exception>
#include <iostream>
#include <unistd.h>
#include <string>
#include <sstream>
#include "worker.cpp"
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



int main(int argc, char const *argv[]){
	Worker<unsigned long int> calc([&](unsigned long int i){ cout << PFact(i) << '\n'; });
	stringstream ss("1\n2\n3\n4\n145\n156\nexit\n999\n");

	unsigned int number = 0;
	for (string line; getline(ss, line, '\n');){
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

	calc.join();

	return 0;
}

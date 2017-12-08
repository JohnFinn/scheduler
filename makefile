a.out: main.o pfact.o
	g++ $^ -std=c++17 -pthread
main.o: main.cpp
	g++ main.cpp -c -std=c++11
pfact.o: ~/Documents/oop/prime_factorizator/pf.cpp ~/Documents/oop/prime_factorizator/pf.h
	g++ -c ~/Documents/oop/prime_factorizator/pf.cpp -std=c++17 -o $@
clean:
	rm main.o pfact.o a.out

a.out: main.o pfact.o
	c++ $^ -std=c++17 -pthread -g
main.o: main.cpp worker.cpp
	c++ main.cpp -c -std=c++17 -g
pfact.o: ~/Documents/oop/prime_factorizator/pf.cpp ~/Documents/oop/prime_factorizator/pf.h
	c++ -c ~/Documents/oop/prime_factorizator/pf.cpp -std=c++17 -o $@
clean:
	rm main.o pfact.o a.out

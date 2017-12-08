a.out: main.o scheduler.o pfact.o
	g++ $^ -std=c++17
main.o: main.cpp
	g++ main.cpp -c -std=c++11
scheduler.o: scheduler.cpp scheduler.h
	g++ scheduler.cpp -c -std=c++11
pfact.o: ~/Documents/oop/prime_factorizator/pf.cpp ~/Documents/oop/prime_factorizator/pf.h
	g++ -c ~/Documents/oop/prime_factorizator/pf.cpp -std=c++17 -o $@
clean:
	rm main.o scheduler.o pfact.o a.out

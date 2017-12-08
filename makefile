a.out: main.o scheduler.o
	g++ $^ -std=c++17
main.o: main.cpp
	g++ main.cpp -c -std=c++11
scheduler.o: scheduler.cpp scheduler.h
	g++ scheduler.cpp -c -std=c++11
clean:
	rm main.o scheduler.o a.out

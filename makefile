default: test

worker.so: worker.cpp
	clang++ $^ -c -o $@ -std=c++17

worker_test: worker.so test.cpp
	clang++ $^ -o $@ -lpthread -lgtest -std=c++17

test: worker_test
	./worker_test

clean:
	rm worker.so worker_test

install: worker.so worker.h
	ln worker.so /lib/libworker.so
	ln worker.h /usr/include/worker.h

uninstall: 
	rm /lib/libworker.so /usr/include/worker.h

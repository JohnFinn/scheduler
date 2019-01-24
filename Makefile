default: test

build/worker.so: worker.cpp
	clang++ $< -c -o $@ -std=c++17

build/detaching_worker.so: detaching_worker.cpp
	clang++ $^ -c -o $@ -std=c++17

build/libworker.a: build/worker.so build/detaching_worker.so
	ar rvs $@ $^

build/worker_test: test.cpp build/libworker.a
	clang++ $^ -o $@ -lpthread -lgtest -std=c++17

test: build/worker_test
	./build/worker_test

clean:
	rm -r build

install: worker.so worker.h
	ln worker.so /lib/libworker.so
	ln worker.h /usr/include/worker.h

uninstall: 
	rm /lib/libworker.so /usr/include/worker.h

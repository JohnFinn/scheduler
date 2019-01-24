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

install: build/libworker.a worker.h detaching_worker.h
	ln $< /lib
	mkdir /usr/include/worker
	ln worker.h detaching_worker.h /usr/include/worker

uninstall: 
	rm -r /lib/libworker.a /usr/include/worker

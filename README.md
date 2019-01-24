installation
```
git clone https://github.com/JohnFinn/worker.git
cd worker
mkdir build
make test
make install
```

usage example
```c++
#include<worker/worker.h>

int main(){
    Worker worker;
	worker.push([&](){
        cout<<"hello world\n";
    });
}
```

compiling example
```
g++ example.cpp -lpthread -lworker
./a.out
```
output:
```
AAA
BBB
CCC
DDD

AAA
DDD
BBB
CCC
```

Tests sometimes fail because sync via sleep.

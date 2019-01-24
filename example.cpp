#include <iostream>

#include <worker/worker.h>
#include <worker/detaching_worker.h>

using namespace std;
using namespace std::chrono_literals;

int main(){
    {
        Worker worker;
        worker.push([&](){
            this_thread::sleep_for(1ms);
            cout << "BBB\n";
        });
        worker.push([&](){
            this_thread::sleep_for(1ms);
            cout << "CCC\n";
        });
        cout << "AAA\n";
    } // Worker will block until it executes all tasks
    cout << "DDD\n\n";

    {
        DetachingWorker worker;
        worker.push([&](){
            this_thread::sleep_for(1ms);
            cout << "BBB\n";
        });
        worker.push([&](){
            this_thread::sleep_for(1ms);
            cout << "CCC\n";
        });
        cout << "AAA\n";
    } // DetachingWorker on the other hand won't block
    // and will execute all tasks, unless program terminates
    cout << "DDD\n";
    this_thread::sleep_for(3ms);
}

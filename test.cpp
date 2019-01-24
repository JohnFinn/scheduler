#include "worker.h"
#include "detaching_worker.h"

#include <stdio.h>
#include <gtest/gtest.h>

using namespace std::chrono_literals;

TEST(Worker_test, push){
	Worker worker;
	bool a = false;
	worker.push([&](){
		std::this_thread::sleep_for(1ms);
		a = true;
	});
	ASSERT_FALSE(a);
	std::this_thread::sleep_for(2ms);
	ASSERT_TRUE(a);
}

TEST(Worker_test, push2){
	bool a = false, b = false, c = false;
	{
		Worker worker;
		worker.push([&](){
			std::this_thread::sleep_for(1ms);
			a = true;
		});
		worker.push([&](){
			std::this_thread::sleep_for(1ms);
			b = true;
		});
		worker.push([&](){
			std::this_thread::sleep_for(1ms);
			c = true;
		});
		ASSERT_FALSE(a or b or c);
	}
	ASSERT_TRUE(a and b and c);
}

TEST(DetachingWorkerTest, push){
    bool a = false;
    DetachingWorker worker;
    worker.push([&](){
        std::this_thread::sleep_for(1ms);
        a = true;
    });
    ASSERT_FALSE(a);
    std::this_thread::sleep_for(2ms);
    ASSERT_TRUE(a);
}

TEST(DetachingWorkerTest, push2){
    bool a = false, b = false, c = false;
    DetachingWorker worker;
    worker.push([&](){
        std::this_thread::sleep_for(1ms);
        a = true;
    });
    worker.push([&](){
        std::this_thread::sleep_for(1ms);
        b = true;
    });
    worker.push([&](){
        std::this_thread::sleep_for(1ms);
        c = true;
    });
    ASSERT_FALSE(a or b or c);
    std::this_thread::sleep_for(1.5ms);
    ASSERT_TRUE(a and !b and !c);
    std::this_thread::sleep_for(1ms);
    ASSERT_TRUE(a and b and !c);
    std::this_thread::sleep_for(1ms);
    ASSERT_TRUE(a and b and c);
}

TEST(DetachingWorkerTest, detach){
    bool a = false, b = false, c = false;
    {
        DetachingWorker worker;
        worker.push([&](){
            std::this_thread::sleep_for(1ms);
            a = true;
        });
        worker.push([&](){
            std::this_thread::sleep_for(1ms);
            b = true;
        });
        worker.push([&](){
            std::this_thread::sleep_for(1ms);
            c = true;
        });
    }
    ASSERT_FALSE(a or b or c);
    std::this_thread::sleep_for(1.5ms);
    ASSERT_TRUE(a and !b and !c);
    std::this_thread::sleep_for(1ms);
    ASSERT_TRUE(a and b and !c);
    std::this_thread::sleep_for(1ms);
    ASSERT_TRUE(a and b and c);
}


int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

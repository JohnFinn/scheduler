#include "worker.h"
#include <stdio.h>
#include <gtest/gtest.h>
#include <memory>

using namespace std::chrono_literals;

TEST(Worker_test, push){
	Worker worker;
	bool a = false;
	worker.push([&](){
		std::this_thread::sleep_for(1ms);
		a = true;
	});
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

int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

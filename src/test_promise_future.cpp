#include "test_promise_future.h"

#include <future>         // std::async, std::future
#include <chrono>         // std::chrono::milliseconds
#include <ctime>
#include <iomanip>

PromiseFutureTest::PromiseFutureTest()
{
}

PromiseFutureTest::~PromiseFutureTest()
{
}

bool PromiseFutureTest::IsPrime(int x)
{
	for (int i=2; i<x; ++i)
	{
		if (x%i==0) 
		{
			std::cout << "return in " << __func__ << std::endl;
			return false;
		}
	}
	std::cout << "return in " << __func__ << std::endl;
	return true;
}

void PromiseFutureTest::PrintTestInfo(const std::string& info)
{
	std::cout << std::string(info.length(), '=') << std::endl;
	std::cout << info << std::endl;
	std::cout << std::string(info.length(), '=') << std::endl;
}

TEST_F(PromiseFutureTest, NormalUse)
{
	PrintTestInfo("Sample code to use std::future with std::async");
	// call function asynchronously:
	const int test_value = 700020007;
	std::future<bool> fut = std::async (std::launch::async, IsPrime, test_value); 

	// do something while waiting for function to set future:
	std::cout << "checking and waiting for IsPrime(" << test_value << ")";
	std::chrono::milliseconds span (10);
	std::future_status wait_res;
	do
	{
		wait_res = fut.wait_for(span);
		EXPECT_NE(wait_res, std::future_status::deferred);
		std::cout << '.';
		std::cout.flush();
	}
	while(wait_res != std::future_status::ready);

	// done
	bool x = fut.get();
    std::cout << "\n700020007 " << (x?"is":"is not") << " prime.\n";
}

TEST_F(PromiseFutureTest, NormalUse2)
{
	PrintTestInfo("Sample code to use std::future with std::promise");
	std::promise<bool> test_promise;
	std::future<bool> test_future = test_promise.get_future();
	bool test_value = true;
	// call function asynchronously:
	std::future<void> fut = std::async(std::launch::async, [&test_promise](bool set_value){
		sleep(3);
		test_promise.set_value(set_value);
	}, test_value);

	// do something while waiting for function to set promise:
	std::cout << "Waiting for promise.set_value() ";
	std::chrono::milliseconds span (10);
	std::future_status wait_res;
	do
	{
		wait_res = test_future.wait_for(span);
		EXPECT_NE(wait_res, std::future_status::deferred);
		std::cout << '.';
		std::cout.flush();
	}
	while(wait_res != std::future_status::ready);
	std::cout << std::endl;

	// done
	bool x = test_future.get();
	EXPECT_EQ(x, test_value);
}

TEST_F(PromiseFutureTest, NegativeTest)
{
	PrintTestInfo("NegativeTest: std::async can be blocking if left value is not assigned");
	{
		// call function asynchronously:
		std::cout << "launch async, but blocking sync instead for left value not assigned .... " << std::endl;
		std::async(std::launch::async, [](){
			sleep(5);
		});
		std::cout << "CONCLUSION: not a real async because left value future has to release after async finish" << std::endl << std::endl;
	}

	{
		// call function asynchronously:
		std::cout << "launch async, with left value assigned to a std::future, make it real async" << std::endl;
		std::future<void> fut = std::async(std::launch::async, [](){
			sleep(5);
		});
		std::cout << "try to out of async" << std::endl;
		std::cout << "future can not release before sync finish, waiting ..." << std::endl;
	}
	std::cout << "future release" << std::endl;
}

#include "test_promise_future.h"

#include <future>         // std::async, std::future
#include <chrono>         // std::chrono::milliseconds

PromiseFutureTest::PromiseFutureTest()
{
	std::cout << __func__ << std::endl;
}

PromiseFutureTest::~PromiseFutureTest()
{
	std::cout << __func__ << std::endl;
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

TEST_F(PromiseFutureTest, NormalUse)
{
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

#include <iostream>
#include "gtest/gtest.h"

//#define TEST_LIBCURL
//#define TEST_UNIQUEPTR
//#define TEST_LOCAL_LIBCURL_MULTI_SOCKET
#define TEST_PROMISE_FUTURE

#ifdef TEST_LIBCURL
#include "test_libcurl.h"
#endif

#ifdef TEST_UNIQUEPTR
#include "test_uniqueptr.h"
#endif

int libcurl_multi_socket_run(void);

#include <future>         // std::async, std::future
#include <chrono>         // std::chrono::milliseconds
#include <unistd.h>

#include <mutex>                // std::mutex, std::unique_lock
#include <condition_variable>    // std::condition_variable

bool is_prime (int x) {
  for (int i=2; i<x; ++i)
  {
	if (x%i==0) 
	{
		std::cout << "return in is_prime" << std::endl;
		return false;
 	}
  }
  std::cout << "return in is_prime" << std::endl;
  return true;
}

void test_promise_func(std::promise<bool>* test_promise)
{
	//sleep(10);
	std::cout << "before promise.set_value" << std::endl;
	test_promise->set_value(true);
	std::cout << "after promise.set_value" << std::endl;
}

void test_condition_var(std::condition_variable* test_condition, std::mutex* mtx_ptr, bool* done_within_func)
{
	sleep(5);
	std::cout << "before set condition" << std::endl;
	std::unique_lock<std::mutex> lck(*mtx_ptr);
	sleep(3);
	test_condition->notify_all();
	*done_within_func = true;
	std::cout << "after set condition" << std::endl;
}

int main(int argc, char **argv)
{
	std::string gtest_filter_str;
#ifdef TEST_LIBCURL
	LibcurlTester lib_curltest;
	lib_curltest.run();	
#endif

#ifdef TEST_UNIQUEPTR
	UniquePtrTester uniqueptr_test;
	uniqueptr_test.RunTests();
#endif

#ifdef TEST_LOCAL_LIBCURL_MULTI_SOCKET
	libcurl_multi_socket_run();
#endif

#ifdef TEST_PROMISE_FUTURE
	gtest_filter_str += "PromiseFutureTest.*";
#endif
	::testing::InitGoogleTest(&argc, argv);
	::testing::GTEST_FLAG(filter) = gtest_filter_str;
	return RUN_ALL_TESTS();

#if 0
// call function asynchronously:
   std::future<bool> fut = std::async (std::launch::async, is_prime,700020007); 

     // do something while waiting for function to set future:
       std::cout << "checking, please wait";
	   std::cout.flush();
         std::chrono::milliseconds span (10);
           //while (fut.wait_for(span)==std::future_status::timeout)
           bool done = false;
			while(!done)
			{
				auto wait_res = fut.wait_for(span);
				if (wait_res == std::future_status::ready)
				{
					done = true;
                 	bool x = fut.get();
                    std::cout << "\n700020007 " << (x?"is":"is not") << " prime.\n";
				}
				else if (wait_res == std::future_status::deferred)
				{
            	   std::cout << '*';
				   std::cout.flush();
				}
				else if (wait_res == std::future_status::timeout)
				{
            	   std::cout << '.';
					std::cout.flush();
					done = true;
				}
			}

	//sleep(10);
#endif

#if 0
	std::promise<bool> test_promise;
	std::future<bool> test_future_promise = test_promise.get_future();

#if 0
	std::async(std::launch::async, [&test_promise](bool test){
		sleep(10);
		std::cout << "before promise.set_value" << std::endl;
		test_promise.set_value(true);
		std::cout << "after promise.set_value" << std::endl;
	}, true);
#else
	std::future<void> test_future = std::async(std::launch::async, test_promise_func, &test_promise);
#endif
		sleep(3);
		std::cout << "Checking promise: " << std::endl;
		test_future_promise.wait();	
         std::chrono::milliseconds span (2);
           //while (fut.wait_for(span)==std::future_status::timeout)
           bool done = false;
			while(!done)
			{
				auto wait_res = test_future.wait_for(span);
				if (wait_res == std::future_status::ready)
				{
					done = true;
                 	bool x = test_future_promise.get();
                    std::cout << "\ntest promise: get " << (x?"true":"false") << " from promise.\n";
				}
				else if (wait_res == std::future_status::deferred)
				{
            	   std::cout << '*';
				   std::cout.flush();
				}
				else if (wait_res == std::future_status::timeout)
				{
            	   std::cout << '.';
					std::cout.flush();
					//done = true;
				}
			}
#endif

#if 0
		std::condition_variable test_condition;	
		std::mutex mtx;

		bool done_within_func = false;
		std::future<void> test_future = std::async(std::launch::async, test_condition_var, &test_condition, &mtx, &done_within_func);
		std::cout << "Checking condition: " << std::endl;
         std::chrono::milliseconds span (2);
           //while (fut.wait_for(span)==std::future_status::timeout)
           bool done = false;
#if 0
			while(!done)
			{
				auto wait_res = test_future.wait_for(span);
				if (wait_res == std::future_status::ready)
				{
					done = true;
                    std::cout << "\ntest condition: condition is set ";
					std::cout.flush();
				}
				else if (wait_res == std::future_status::deferred)
				{
            	   std::cout << '*';
				   std::cout.flush();
				}
				else if (wait_res == std::future_status::timeout)
				{
            	   std::cout << '.';
					std::cout.flush();
					//done = true;
				}
			}
#else
		//sleep(10);
		while(!done)
		{
			std::unique_lock<std::mutex> l(mtx);
			auto wait_res = test_condition.wait_for(l,std::chrono::milliseconds(200), [done_within_func](){return done_within_func;});
			//if (wait_res ==std::cv_status::timeout)
			if (!wait_res)
			{
            	   std::cout << '.';
					std::cout.flush();
			}
			///else if (wait_res== std::cv_status::no_timeout)
			else
			{
					done = true;
                    std::cout << "\ntest condition: condition is set ";
					std::cout.flush();
			}
		}

#endif
#endif

	std::cout << "return in main" << std::endl;
  	return 0;
}


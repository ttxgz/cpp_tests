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

  	return 0;
}


#include <iostream>

#define TEST_LIBCURL
#define TEST_UNIQUEPTR

#ifdef TEST_LIBCURL
#include "test_libcurl.h"
#endif

#ifdef TEST_UNIQUEPTR
#include "test_uniqueptr.h"
#endif

int main(void)
{
#ifdef TEST_LIBCURL
	LibcurlTester lib_curltest;
	lib_curltest.run();	
#endif

#ifdef TEST_UNIQUEPTR
	UniquePtrTester uniqueptr_test;
	uniqueptr_test.RunTests();
#endif

  	return 0;
}


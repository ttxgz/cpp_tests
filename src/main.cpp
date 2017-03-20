#include <iostream>

//#define TEST_LIBCURL
//#define TEST_UNIQUEPTR
#define TEST_LOCAL_LIBCURL_MULTI_SOCKET

#ifdef TEST_LIBCURL
#include "test_libcurl.h"
#endif

#ifdef TEST_UNIQUEPTR
#include "test_uniqueptr.h"
#endif

int libcurl_multi_socket_run(void);

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

#ifdef TEST_LOCAL_LIBCURL_MULTI_SOCKET
	libcurl_multi_socket_run();
#endif

  	return 0;
}


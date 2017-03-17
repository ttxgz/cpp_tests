#include "test_libcurl.h"
#include "test_uniqueptr.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <fstream>

using namespace std;

#include <vector>

#include <memory>
#include <functional>
#include <utility>

//#define TEST_LIBCURL
#define TEST_UNIQUEPTR
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


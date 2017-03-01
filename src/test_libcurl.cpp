#include "test_libcurl.h"


bool LibcurlTester::global_inited = false;

//bool global_inited=false;

LibcurlTester::LibcurlTester()
{
	std::cout << "libcurl_test()" << std::endl;
#if 1
	GlobalInit();
	curl_handler = curl_easy_init();
	if (curl_handler)
		inited_successful = true;
#endif
}

bool LibcurlTester::GlobalInit()
{
#if 1
	if (global_inited)
		return true;
	CURLcode res = curl_global_init(CURL_GLOBAL_DEFAULT);	
	if(res != CURLE_OK)
	{
    	std::cerr << "curl_global_init() failed: " << curl_easy_strerror(res) << std::endl;
    	return false;
  	}
	global_inited = true;
#else
	return true;
#endif

}

bool LibcurlTester::GlobalDeInit()
{
#if 1
	if (!global_inited)
		return true;
	curl_global_cleanup();
#endif
	return true;
}

void LibcurlTester::run()
{
	std::cout << "libcurl_test::run()" << std::endl;
}


#ifndef LIB_CURL
#define LIB_CURL

#include <string>
#include <curl/curl.h>

class LibcurlTester{
public:
	LibcurlTester();
	~LibcurlTester();
	void run();

	bool inited_successful;

private:
	static bool GlobalInit();
	static bool GlobalDeInit();
	static size_t ReadCallback(void *ptr, size_t size, size_t nmemb, void *userp);
	static int Trace(CURL* handle, curl_infotype type, char* data, size_t size, void* userptr);

	static size_t curl_inst_num;
	static bool global_inited;

	CURL* curl_handler;
	std::string data;
};

#endif


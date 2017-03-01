#include "test_libcurl.h"


bool LibcurlTester::global_inited = false;
size_t LibcurlTester::curl_inst_num = 0;

LibcurlTester::LibcurlTester()
{
	// TODO: shold protect by scope lock
	GlobalInit();
	curl_handler = curl_easy_init();
	if (curl_handler)
	{
		inited_successful = true;
		curl_inst_num++;
	}
	// end of scoped lock

	CURLcode err = CURLE_OK;

	// set fresh connection
	err = curl_easy_setopt(curl_handler, CURLOPT_FORBID_REUSE, 1L);	
	if (err != CURLE_OK)
	{
		std::cerr << "failed in init curl: set forbid reuse failure code with " << err << std::endl;
		inited_successful = false;
		return;
	}
	err = curl_easy_setopt(curl_handler, CURLOPT_FRESH_CONNECT, 1L);	

	// set debug
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
	curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, Trace);
	curl_easy_setopt(curl, CURLOPT_DEBUGDATA, this);

	// set method
	err = curl_easy_setopt(curl_handler, CURLOPT_POST, 1L);	

	// set read callback
	curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
	curl_easy_setopt(curl, CURLOPT_READDATA, this);

	// set timerout
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);
}

LibcurlTester::~LibcurlTester()
{
	// TODO: shold protect by scope lock
	if (global_inited && curl_handler)
	{
		curl_easy_cleanup(curl_handler);
		curl_inst_num--;
		if (curl_inst_num == 0)
		{
			GlobalDeInit();
			global_inited = false;
		}
	}
}

bool LibcurlTester::GlobalInit()
{
	if (global_inited)
		return true;
	CURLcode res = curl_global_init(CURL_GLOBAL_DEFAULT);	
	if(res != CURLE_OK)
	{
    	std::cerr << "curl_global_init() failed: " << curl_easy_strerror(res) << std::endl;
    	return false;
  	}
	global_inited = true;
	return true;
}

bool LibcurlTester::GlobalDeInit()
{
	if (!global_inited)
		return true;

	curl_global_cleanup();
	return true;
}

void LibcurlTester::run()
{
	CURLcode err = CURLE_OK;
	std::cout << "libcurl_test::run()" << std::endl;
	curl_easy_setopt(curl_handler, CURLOPT_URL, "https://www.google.com/");
	std::string upload_data (1024, 'c'); // upload 1KB per POST connection
	curl_easy_setopt(curl_handler, CURLOPT_POSTFIELDSIZE, upload_data.size());
	while(1)
	{
		data = upload_data;
		err = curl_easy_perform(curl_handler);
		if(err != CURLE_OK)
		{
			std::cerr << "curl_easy_perform() failed: " << curl_easy_sterror(err) << std::endl;
		}
	}
}

size_t LibcurlTester::ReadCallback(void *ptr, size_t size, size_t nmemb, void *userp)
{
	LibcurlTester* curl = static_cast<LibcurlTester*>(userp);

	if(size*nmemb < 1)
  		return 0;

	size_t read_bytes = std::min(size*nmemb, curl->data.size());
	if (read_bytes > 0)
	{
		std::cout << "begin to copy " << read_bytes << " data:" << std::endl;
		std::cout << curl->data << std::endl;
		memcpy(ptr, data.c_str(), read_bytes);
		std::cout << "end to copy data" << std::endl;
		curl->data.erase(0, read_bytes);
	}
	else
	{
		std::cout << "finish data uploading" << std::endl;
	}
	return read_bytes;                        /* no more data left to deliver */ 
}

static int LibcurlTester::Trace(CURL* handle, curl_infotype type, char* data, size_t size, void* userptr)
{

    const char *text;
    switch (type) {
    case CURLINFO_TEXT:
        text = "=> Info";
        break;
    case CURLINFO_HEADER_OUT:
        text = "=> Send header";
        break;
    case CURLINFO_DATA_OUT:
        text = "=> Send data";
        break;
    case CURLINFO_SSL_DATA_OUT:
        text = "=> Send SSL data";
        break;
    case CURLINFO_HEADER_IN:
        text = "<= Recv header";
        break;
    case CURLINFO_DATA_IN:
        text = "<= Recv data";
        break;
    case CURLINFO_SSL_DATA_IN:
        text = "<= Recv SSL data";
        break;
    default:
        text = "<= UNKNOWN cURL type";
        break;
    }

    if (text != "=> Send data")
    {
        std::string data_dump(data, size);
        std::cout << text << size << "bytes" << std::endl;
        std::cout << data_dump << std::endl;
    }
    return 0;
}


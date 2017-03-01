#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <string.h>

using namespace std;

#include <curl/curl.h>
#include <sys/types.h>
#include <errno.h>


////#define LIMIT_LOCAL_TCP_PORT
////const char data[]="this is what we post to the silly web server";
//
////const char data[]="this";
//const std::string data((size_t)(1024*12), 'a');
// 
//struct WriteThis {
//  const char *readptr;
//  long sizeleft;
//};
// 
//static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *userp)
//{
//  struct WriteThis *pooh = (struct WriteThis *)userp;
// 
//  if(size*nmemb < 1)
//    return 0;
// 
//  //if(pooh->sizeleft) {
//  //  *(char *)ptr = pooh->readptr[0]; /* copy one single byte */ 
//  //  pooh->readptr++;                 /* advance pointer */ 
//  //  pooh->sizeleft--;                /* less data left */ 
//  //  return 1;                        /* we return 1 byte at a time! */ 
//  //}
//  std::cout << "begin to copy " << data.size() << " data " << std::endl;
//  memcpy(ptr, data.c_str(), data.size());
//  std::cout << "end to copy data" << std::endl;
// 
//  return data.size();                        /* no more data left to deliver */ 
//}
// 
//
//static int Trace(CURL* handle, curl_infotype type, char* data, size_t size, void* userptr)
//{
//	
//	const char *text;
//	switch (type) {
//	case CURLINFO_TEXT:
//		text = "=> Info";
//		break;
//	case CURLINFO_HEADER_OUT:
//		text = "=> Send header";
//		break;
//	case CURLINFO_DATA_OUT:
//		text = "=> Send data";
//		break;
//	case CURLINFO_SSL_DATA_OUT:
//		text = "=> Send SSL data";
//		break;
//	case CURLINFO_HEADER_IN:
//		text = "<= Recv header";
//		break;
//	case CURLINFO_DATA_IN:
//		text = "<= Recv data";
//		break;
//	case CURLINFO_SSL_DATA_IN:
//		text = "<= Recv SSL data";
//		break;
//	default: 
//		text = "<= UNKNOWN cURL type";
//		break;
//	}
//
//	if (text != "=> Send data")
//	{
//		std::string data_dump(data, size);
//		std::cout << text << size << "bytes" << std::endl;
//		std::cout << data_dump << std::endl;
//	}
//	return 0;
//}

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


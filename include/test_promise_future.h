#ifndef PROMIS_FUTURE_H_ 
#define PROMIS_FUTURE_H_ 

#include "gtest/gtest.h"

//#include <string>
//#include <functional>
//#include <list>

//typedef std::function<bool(void)> TestCase;
//class UniquePtrTester{
//public:
//
//	UniquePtrTester();
//	bool RunTests();
//
//private:
//	std::list<TestCase> testcases;
//	std::string purpose;
//	void AddTestCase(TestCase& new_case);
//
//	bool CustomDeletor();
//	bool DoubleDelByPtrValueAssign();
//};

class PromiseFutureTest : public testing::Test
{
public:
	PromiseFutureTest();
	virtual ~PromiseFutureTest();

	void PrintTestInfo(const std::string& info);


	static bool IsPrime(int x);
	
};
#endif


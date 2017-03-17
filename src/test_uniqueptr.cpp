#include "test_uniqueptr.h"
#include <iostream>
#include <memory>


UniquePtrTester::UniquePtrTester()
{
	TestCase testcase = [&](){return CustomDeletor();};
	AddTestCase(testcase);

	testcase = [&](){return DoubleDelByPtrValueAssign();};
	AddTestCase(testcase);
}

void UniquePtrTester::AddTestCase(TestCase& new_case)
{
	testcases.push_back(new_case);
	return;
}

bool UniquePtrTester::RunTests()
{
	bool res = true;
	for (auto& testcase : testcases)
	{
		if (!testcase())
		{
			res = false;
		}
	}
	return res;
}

bool UniquePtrTester::CustomDeletor()
{
	bool res = true;
	purpose = "Show how to create custom deletor to unique_ptr";
	std::string SEPERATOR_LINE(purpose.size() + 20, '=');
	std::cout << std::endl << SEPERATOR_LINE << std::endl;
	std::cout << __func__ << ": " << purpose << std::endl;
	std::cout << SEPERATOR_LINE << std::endl;

	auto del = [](std::string* p) 
	{
		std::cout << "Custom Deletor: Deleting unique_ptr<std::string>, value is : " << *p << std::endl;
	};

	std::string a_value("abbbbbbb");
	std::unique_ptr<std::string, decltype(del)> a(nullptr, del);
	a.reset(new std::string{"bbbb"});
	a.reset(&a_value);

	return res;
}

bool UniquePtrTester::DoubleDelByPtrValueAssign()
{
	bool res = true;
	purpose = "Be carefule for double deletion when reset unique_ptr with ptr value assignment";
	std::string SEPERATOR_LINE(purpose.size() + 20, '=');
	std::cout << std::endl << SEPERATOR_LINE << std::endl;
	std::cout << __func__ << ": " << purpose << std::endl;
	std::cout << SEPERATOR_LINE << std::endl;

	auto del = [](std::string* p) 
	{
		std::cout << "Custom Deletor: Deleting unique_ptr<std::string>, value is : " << *p << std::endl;
	};

	std::string before_ptr("instance create before unique_ptr");
	std::unique_ptr<std::string, decltype(del)> a(nullptr, del);
	std::string after_ptr("instance create before unique_ptr");

	a.reset(&before_ptr);
	std::cout << "unique_ptr is going to reset(double deletion at the end of the func):" << std::endl;
	a.reset(&after_ptr);
	std::cout << "unique_ptr is going to reset(double deletion at the end of the func), but ptr is already invalid:" << std::endl;

	return res;
}

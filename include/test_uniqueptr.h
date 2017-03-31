#ifndef LIB_UNIQUEPTR
#define LIB_UNIQUEPTR

#include <string>
#include <functional>
#include <list>

typedef std::function<bool(void)> TestCase;
class UniquePtrTester{
public:

	UniquePtrTester();
	bool RunTests();

private:
	std::list<TestCase> testcases;
	std::string purpose;
	void AddTestCase(TestCase& new_case);

	bool CustomDeletor();
	bool DoubleDelByPtrValueAssign();
};

#endif


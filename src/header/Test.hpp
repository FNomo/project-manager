# ifndef _TEST 
# define _TEST

# include <iostream>
# include <vector>
using namespace std;

typedef bool (*test_function)();

enum TestResult{FAILED, SUCCEED};

class TestSheme{
	private:
		TestSheme();
		static int ID;
		int id;
		string title;
		string description;
		test_function fun;
		TestResult result;
	friend class Test;
};

class Test{
	protected:
		static TestSheme create_testsheme(string, string, test_function);

	public:
		static void run(vector<TestSheme>);
};

# endif
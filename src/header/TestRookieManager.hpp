# ifndef _TEST_ROOKIE
# define _TEST_ROOKIE

# include "Test.hpp"

class Task;
class TestRookieManager: public Test{
	private:
		static bool test0();
		static bool test1();
		static bool test2();
	public:
		static vector<Task*> EXPECTED_RESULT;
		static void run();
};

# endif
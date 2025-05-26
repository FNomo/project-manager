# ifndef _TEST_EXPERT
# define _TEST_EXPERT

# include "Test.hpp"

class Task;
class TestExpertManager: public Test{
	private:
		static bool test0();
		static bool test1();
		static bool test2();
		static bool test3();
	public:
		static vector<Task*> EXPECTED_RESULT;
		static void run();
};

# endif
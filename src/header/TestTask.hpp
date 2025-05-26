# ifndef _TEST_TASK
# define _TEST_TASK

# include "Test.hpp"

class TestTask: public Test{
	private:
		static bool test0();
		static bool test1();
		static bool test2();
		static bool test3();
		static bool test4();
		static bool test5();
		static bool test6();

	public:
		static void run();
};

# endif
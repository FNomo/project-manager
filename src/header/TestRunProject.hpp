# ifndef _TEST_RUN
# define _TEST_RUN

# include "Test.hpp"

class TestRunProject: public Test{
	private:
		static bool test0();
		static bool test1();

	public:
		static void run();
};

# endif
# ifndef _TEST_PROTO
# define _TEST_PROTO

# include "Test.hpp"

class TestProtoProject: public Test{
	private:
		static bool test0();
		static bool test1();
		static bool test2();
		static bool test3();
		static bool test4();
		
	public:
		static void run();
};

# endif

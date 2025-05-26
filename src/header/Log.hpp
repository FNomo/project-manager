# ifndef _LOG 
# define _LOG

# include <iostream>
# include <vector>
# include <fstream>
using namespace std;

class Log{
	private:
		static ofstream LOG_STREAM;
		static vector<string> CONTEXTS;
		static void print(string, string);

	public :
		static int init();
		static void close();
		static void add_context(string);
		static void remove_context();
		static void d(string);
		static void e(string);
		static void v(string);
		static void i(string);
};

# endif
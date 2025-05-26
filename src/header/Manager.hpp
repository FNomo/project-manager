# ifndef _MANAGER 
# define _MANAGER

# include <iostream>
# include <vector>
# include "RunProject.hpp"
using namespace std;

class Manager{
	private:
		static int ID;
		int id;

	protected:
		Manager(string);
		string category;

	public:
		Manager(Manager&) = delete;
		virtual ~Manager();
		virtual pair<vector<int>, int> advise(const RunProject&) = 0;
		friend ostream& operator<<(ostream&, const Manager&);
};

# endif
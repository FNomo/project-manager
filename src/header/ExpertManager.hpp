# ifndef _EXPERT
# define _EXPERT

# include "Manager.hpp"
# include "RunProject.hpp"

class ExpertManager: public Manager{
	public:
		ExpertManager();
		ExpertManager(ExpertManager&) = delete;

		virtual pair<vector<int>, int> advise(const RunProject&);

};

extern int IS_TESTED ;

# endif
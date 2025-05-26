# ifndef _ROOKIE
# define _ROOKIE

# include "Manager.hpp"
# include "RunProject.hpp"

class RookieManager: public Manager{
	public:
		RookieManager();
		RookieManager(RookieManager&) = delete;

		virtual pair<vector<int>, int> advise(const RunProject&);

};

extern int IS_TESTED ;

# endif
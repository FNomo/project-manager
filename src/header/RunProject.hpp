# ifndef _RUNPROJECT 
# define _RUNPROJECT

# include <iostream>
# include <vector>
# include "Project.hpp"
using namespace std;

class TestRunProject;
class ProtoProject;
class TestRookieManager;
class TestExpertManager;
class Project;

class RunProject: public Project{

	public:
		RunProject() = delete;
		RunProject(const RunProject&) = delete;
		RunProject(const ProtoProject&);
		virtual ~RunProject();

		int run(int);
		int run(vector<int>);
		ostream& afficher(ostream& os)const;

		friend ostream& operator<<(ostream &os,RunProject &proto);
		friend TestRunProject;
		friend TestRookieManager;
		friend TestExpertManager;
};

# endif

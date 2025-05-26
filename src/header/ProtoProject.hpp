# ifndef _PROTOPROJECT 
# define _PROTOPROJECT

# include <iostream>
# include <vector>
# include "Project.hpp"
# include "Task.hpp"

using namespace std;

class TestRunProject;
class TestProtoProject;
class TestRookieManager;
class TestExpertManager;

class ProtoProject: public Project{
	private:
		Task *starting_task, *ending_task;
		ostream& afficher(ostream& os)const;
		bool topological_sort();

	public:
		ProtoProject();
		ProtoProject(const ProtoProject&) = delete;
		virtual ~ProtoProject();


		bool add(string, int);
		bool add(string, int, int);
		bool add(string, int, int, int);
		
		vector<Task *> get_all_tasks()const;

		friend ostream& operator<<(ostream &os,ProtoProject &proto);
		friend TestProtoProject;
		friend TestRunProject;
		friend TestRookieManager;
		friend TestExpertManager;

		static Task* expected_tsk;
		static Task* expected_tsk1;
		static Task* expected_tsk2;

};

extern int IS_PROTO_TESTED ;

# endif

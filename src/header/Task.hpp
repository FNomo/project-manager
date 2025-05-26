# ifndef _TASK 
# define _TASK

# include <iostream>
# include <vector>
# include "RunProject.hpp"
using namespace std;

# define DEFAULT_NAME "T"

enum TaskState {PENDING, DONE};

class TestTask;
class TestRookieManager;
class TestExpertManager;
class TestProtoProject;
class TestRunProject;

class Task{
	private:
		static int ID;
		int id, duration;
		string name;
		TaskState state;
		vector<Task*> dependencies;

		void set_id(int);
		void set_duration(int);
		void set_name(string);
		void set_state(TaskState);
		void set_dependencies(const vector<Task*>&);
		bool done();
	
	public: 
		bool mark = false;

		Task();
		Task(int);
		Task(string);
		Task(string, int);
		Task(const Task&);
		virtual ~Task();

		bool depends_from(const Task&) const;
		bool add_dependency(Task&);
		int paral_duration() const;

		const bool isDone() const;
		const bool isRunnable()const;
		const int getId() const;
		const int getDuration() const;
		const string getName() const;
		const vector<Task*> getDependencies() const;

		friend ostream& operator<<(ostream&, const Task&);
		friend class TestTask;
		friend class TestRookieManager;
		friend class TestExpertManager;
		friend class TestProtoProject;
		friend class TestRunProject;
		friend int RunProject::run(int);

		/** fonction servant au Projet */
		bool remove_dependency(const int k);
		void PP_postfixe(vector<Task*> &vecToTravers);

};

# endif
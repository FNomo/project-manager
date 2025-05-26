# ifndef _PROJECT 
# define _PROJECT

# include <iostream>
# include <vector>
# include <utility>


using namespace std;
class Project;
class ProtoProject;
class TestProtoProject;
class Task;
class Project{
	private:
		string category;
	protected:
		vector<Task *> all_tasks;
		pair<int, int> pick_two_random_tasks();
		Task* contains(int);
		Task* contains(string);
		bool topological_sort();
		//méthode supplémentaire;
		pair <int,int> random_id();
		int get_size()const;
		void cleanMarks();
		Project(string);
		string afficher()const;

	public:
		
		Project(Project&) = delete;
		virtual ~Project();
		const vector<Task*> consult_tasks()const;
		
		bool fill_vector(vector<Task*>);
		friend class TestProtoProject;
		
};

# endif

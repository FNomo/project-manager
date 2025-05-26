#include"Project.hpp"
#include"Log.hpp"
#include"Task.hpp"
#include"ProtoProject.hpp"
#include<vector>
#include<algorithm>
#include<iostream>
#include <stdio.h>
#include <sstream>
// class Task;

// constructor for contains:
Project::Project(string _category):category{_category}{
	char message[BUFSIZ];
	sprintf(message,"new Project(%s) %p has been created.",this->category.c_str(),this);
	Log::d(message);
}

Project::~Project(){
	char message[BUFSIZ];
	sprintf(message,"new Project(%s) %p has been destructed.",this->category.c_str(),this);
	Log::d(message);
}

Task* Project::contains(int id){
	for(size_t i = 0; i<all_tasks.size(); i++){
		if(this->all_tasks[i]->getId()==id){
			return this->all_tasks[i];
		}
	};
	return nullptr;
}

Task* Project::contains(string name){
	for(size_t i = 0; i< (this->all_tasks.size());i++){
		if(this->all_tasks[i]->getName()==name){
			return this->all_tasks[i];
		}
	}

	return nullptr;
}

pair<int, int> Project::pick_two_random_tasks(){

	pair<int,int> p = {-1,-2};
	bool dependent=false;
	size_t count = (this->all_tasks.size())*50;
	srand(time(nullptr));
	while(count>=0){
		count--;
		p=this->random_id();
		dependent= this->all_tasks[p.first]->depends_from(*this->all_tasks[p.second]);
		if(dependent){
			continue;
			}
		else{
			p.first=this->all_tasks[p.first]->getId();
			p.second=this->all_tasks[p.second]->getId();
			break;
			}
	}
	return p;
}
pair <int,int>  Project::random_id(){
	int s=int(this->all_tasks.size());
	pair<int,int>p;
	int x=0,y=0;
	while(x==y){
	x ={rand()%s};
	y ={rand()%s};
	}
	p.first=x;
	p.second=y;
	return p;
}

const vector<Task*> Project::consult_tasks()const{
	const vector<Task *> result= vector<Task*>(this->all_tasks);
	return result; 
}

int Project::get_size()const{
	return int(this->all_tasks.size());
}

// clean Marks est utilsier pour effacer les marks avant d'effectuer le tri topologique
void Project::cleanMarks(){
    int s = this->get_size();
    for(int i=0;i<s;i++){
        this->all_tasks[i]->mark=false;
    }
}

bool Project::topological_sort(){

	vector<Task*> Tasks;
	Tasks.clear();
	this->cleanMarks();
	//for( int i =0; i <s ;i++){
		this->all_tasks[0]->PP_postfixe(Tasks);
		// Tasks.push_back(this->all_tasks[i]);
   // }
	if(Tasks.size()==this->all_tasks.size()){	
		reverse(Tasks.begin(),Tasks.end());
		this->all_tasks=Tasks;
		return true;
	}
	else {
		return false;
	}
}
bool Project::fill_vector(vector<Task*>vec){
	this->all_tasks.clear();
	for(Task *t:vec){
		this->all_tasks.push_back(t);
	}
	return true;
}
string Project::afficher()const{
	stringstream os;

	os << "Project(" << category << ") = ["; 
	for (Task* t: this->all_tasks){
		os << t->getName() << "("<< t->getId() <<")";
		if (this->all_tasks.back()->getId() != t->getId() ) os << " - ";
	}
	os << "]";
	return os.str();
}


# include "Task.hpp"
# include "Log.hpp"
# include "Util.hpp"


# include <iostream>
# include <vector>
# include <stdio.h>
# include <sstream>
# include <string.h>
using namespace std;

int Task::ID = 0;
string TaskStateName[] = {"PENDING", "DONE"};

/* ------------------------- *//* ----- Constructeurs ----- *//* ------------------------- */
/* ------------------------- *//* ------------------------- *//* ------------------------- */

/**
 * Construit une tache vide.
*/
Task::Task(): id{ID++}, duration{0}, name{DEFAULT_NAME}, state{PENDING}, dependencies{}{
	stringstream ss;
	ss << DEFAULT_NAME << id;
	ss >> name;
	char message[BUFSIZ];
	sprintf(message, "New Task(%s) %p has been created.", name.c_str(), this);
	Log::d(message);
}

/**
 * Construit une tache avec une durée déterminée
 * @param _duration durée à modifier
*/
Task::Task(int _duration): Task{}{
	this->set_duration(_duration);
}

/**
 * Construit une tache à partir d'un nom.
 * @param _name le nom de la tache
*/
Task::Task(string _name): Task{}{
	this->set_name(_name);
}

/**
 * Construit une tâche à partir d'un nom et d'une durée
 * @param _name le nom de la tâche
 * @param _duration la durée de la tâche
*/
Task::Task(string _name, int _duration): Task{_name} {
	this->set_duration(_duration);
}

/**
 * Construit une tâche à partir d'une autre tache.
 * @param _task la tache source
*/
Task::Task(const Task& _task): Task{}{
	this->set_id(_task.id);
	this->set_name(_task.name);
	this->set_duration(_task.duration);
	this->set_state(_task.state);
	this->set_dependencies(_task.dependencies);
}

/* ------------------------- *//* ------------------------- *//* ------------------------- */
/* ------------------------- *//* ------------------------- *//* ------------------------- */





/* ------------------------ *//* ----- Destructeurs ----- *//* ------------------------ */
/* ------------------------ *//* ------------------------ *//* ------------------------ */

/**
 * Détruit une tache.
*/
Task::~Task(){
	char message[BUFSIZ];
	sprintf(message, "Task(%s) %p has been destructed.", name.c_str(), this);
	Log::d(message);
}

/* ------------------------ *//* ------------------------ *//* ------------------------ */
/* ------------------------ *//* ------------------------ *//* ------------------------ */





/* ---------------------- *//* ----- Accesseurs ----- *//* ---------------------- */
/* ---------------------- *//* ---------------------- *//* ---------------------- */

/**
 * @return `true` si la tâche à été effectuer sinon `false`
*/
const bool Task::isDone() const{
	return this->state == DONE;
}

/**
 * @return le nom de la tâche
*/
const string Task::getName() const{
	return this->name;
}

/**
 * @return l'identifiant de la tâche
*/
const int Task::getId() const{
	return this->id;
}

/**
 * @return la durée de la tâche
*/
const int Task::getDuration() const{
	return this->duration;
}

/**
 * @return les dépendances de la tâche
*/
const vector<Task*> Task::getDependencies() const{
	const vector<Task*> list = vector<Task*>(this->dependencies);
	return list;
}

// nous retourne true si la tache appellante peut être executer
const bool Task::isRunnable()const{
	
	for(Task*t:this->dependencies){
		if(t->state==PENDING){
			return false;
		}
	}
	return true;
}


/* ---------------------- *//* ---------------------- *//* ---------------------- */
/* ---------------------- *//* ---------------------- *//* ---------------------- */





/* ------------------------- *//* ----- Modificateurs ----- *//* ------------------------- */
/* ------------------------- *//* ------------------------- *//* ------------------------- */

/**
 * Change l'identifiant d'une tache.
 * @param _new_id le nouveau id
*/
void Task::set_id(int _new_id){
	int previous_id = this->id;
	this->id = _new_id;
	char message[BUFSIZ];
	sprintf(message, "Task(%s) %p id has changed: %d -> %d.", this->name.c_str(), this, previous_id, this->id);
	Log::d(message);
}

/**
 * Change la durée d'une tache.
 * @param _new_duration le nouveau nom
*/
void Task::set_duration(int _new_duration){
	int previous_duration = this->duration;
	this->duration = _new_duration;
	char message[BUFSIZ];
	sprintf(message, "Task(%s) %p duration has changed: %d -> %d.", this->name.c_str(), this, previous_duration, this->duration);
	Log::d(message);
}

/**
 * Change le nom d'une tache.
 * @param _new_state le nouveau nom
*/
void Task::set_state(TaskState _new_state){
	if (_new_state != DONE) return;
	TaskState previous_state = this->state;
	this->state = _new_state;
	char message[BUFSIZ];
	sprintf(message, "Task(%s) %p state has changed: %s -> %s.", this->name.c_str(), this, TaskStateName[previous_state].c_str(), TaskStateName[this->state].c_str());
	Log::d(message);
}

/**
 * Change le nom d'une tache.
 * @param _new_name le nouveau nom
*/
void Task::set_name(string _new_name){
	string previous_name = this->name;
	this->name = _new_name;
	char message[BUFSIZ];
	sprintf(message, "Task %p name has changed: %s -> %s.", this, previous_name.c_str(), this->name.c_str());
	Log::d(message);
}

/**
 * Change les dépendances de la tache.
 * @param _new_dependencies les nouvelles dépendances
*/
void Task::set_dependencies(const vector<Task*>& _new_dependencies){
	vector<Task*> previous_dependencies = vector<Task*>();

	for (Task *t: this->dependencies)
		if (t != nullptr) previous_dependencies.push_back(t);
	
	this->dependencies = vector<Task*>();
	for (Task *t: _new_dependencies)
		if (t != nullptr) this->dependencies.push_back(t);
	

	char message[BUFSIZ], prev_str[500] = "", new_str[500] = "", elem[10];

	for (Task *t: previous_dependencies){
		if (t == nullptr) continue;
		if (t->id != _new_dependencies.back()->id) sprintf(elem, "%s(%d) - ", t->name.c_str(), t->id);
		else sprintf(elem, "%s(%d)", t->name.c_str(), t->id);
		strcat(prev_str, elem);
	}

	for (Task *t: _new_dependencies){
		if (t == nullptr) continue;
		if (t->id != _new_dependencies.back()->id) sprintf(elem, "%s(%d) - ", t->name.c_str(), t->id);
		else sprintf(elem, "%s(%d)", t->name.c_str(), t->id);
		strcat(new_str, elem);
	}

	sprintf(message, "Task(%s) %p dependencies has changed: [%s] -> [%s].", this->name.c_str(), this, prev_str, new_str);
	Log::d(message);
}

bool Task::remove_dependency(const int k){
	bool result = false;

	if(k>=0 && k<int(this->dependencies.size())){
		this->dependencies.erase(this->dependencies.begin()+k);
	 	result =  true;
	}
	
	return result;
}

// parcour en profondeur demandé pour le tri topologique
void Task::PP_postfixe(vector<Task*> &vecToTravers){
	if(!this->mark){
		
		//this->mark=true;
		int s=int(this->dependencies.size());
		for (int i=0;i<s;i++){
			dependencies[i]->PP_postfixe(vecToTravers);
			//here ?
		}
		vecToTravers.push_back(this);
		this->mark=true;
	}
}


/* ------------------------- *//* ------------------------- *//* ------------------------- */
/* ------------------------- *//* ------------------------- *//* ------------------------- */





/* --------------------- *//* ----- Affichage ----- *//* --------------------- */
/* --------------------- *//* --------------------- *//* --------------------- */

ostream& operator<<(ostream& _out, const Task& _task){
	_out << _task.name << "(" << _task.id << "): ";
	_out << "state [" << TaskStateName[_task.state] << "], ";
	_out << "duration [" << _task.duration << "], ";
	_out << "dependancies [";

	for (Task *task: _task.dependencies){
		if (task != nullptr){
			_out << task->name << "(" << task->id << ")";
			if (task->id != _task.dependencies.back()->id) _out << " - ";
		}
	}

	_out << "]" << endl;
	return _out;
}

/* --------------------- *//* --------------------- *//* --------------------- */
/* --------------------- *//* --------------------- *//* --------------------- */





/* ---------------------- *//* ----- Opérateurs ----- *//* ---------------------- */
/* ---------------------- *//* ---------------------- *//* ---------------------- */

/**
 * Réalisation d'une tache après vérification des dépendances.
 * @return `true` si la tache a bien été réalisé sinon `false`
*/
bool Task::done(){
	bool done_state = true;

	for (Task *task: this->dependencies){
		if (task->state != DONE){
			done_state = false;
			break;
		}
	}

	if (done_state) 
		this->set_state(DONE);
	return done_state;
}

/**
 * Indique si la tache dépends transitivement d'une autre tache
 * @param _task la tache à juger
 * @return `true` si dépendance sinon `false`
*/
bool Task::depends_from(const Task& _task) const{
	bool depends_state = false;

	for (Task *task: this->dependencies){
		if (task == nullptr) continue;

		else if (task->id == _task.id){
			depends_state = true;
			break;
		}

		else if (task->depends_from(_task)){
			depends_state = true;
			break;
		}
	}

	return depends_state;
}

/**
 * Ajoute une dépendance à la tache courante en veiller à ne pas créer de cycle
 * @param _task la tache à ajouter
 * @return `true` en cas de succès sinon `false`
*/
bool Task::add_dependency(Task& _task){
	bool adding_state = false;
	
	if (! _task.depends_from(*this)){
		this->dependencies.push_back(&_task);
		adding_state = true;

		char message[BUFSIZ];
		sprintf(message, "Task(%s) %p has added Task(%s) %p to dependencies.", this->name.c_str(), this, _task.name.c_str(), &_task);
		Log::d(message);
	}

	return adding_state;
}

/**
 * Calcule la durée totale de la réalisation de la tâche ne tenant compte des dépendances
 * @return la durée totale de réalisation de la tâche
*/
int Task::paral_duration() const{
	int global_duration = this->duration, max_dependancy_duration;
	vector<int> dependencies_duration = vector<int>();

	for (Task *task: this->dependencies)
		if (task!= nullptr && task->state != DONE) 
			dependencies_duration.push_back(task->paral_duration());
		
	max_dependancy_duration = Util::max(dependencies_duration);

	if (max_dependancy_duration > 0) global_duration += max_dependancy_duration;
	return global_duration;
}

/* ---------------------- *//* ---------------------- *//* ---------------------- */
/* ---------------------- *//* ---------------------- *//* ---------------------- */
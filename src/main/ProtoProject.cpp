#include"Project.hpp"
#include"ProtoProject.hpp"
#include<sstream>

int IS_PROTO_TESTED = false;
Task* ProtoProject::expected_tsk = nullptr;
Task* ProtoProject::expected_tsk1 = nullptr;
Task* ProtoProject::expected_tsk2 = nullptr;

ProtoProject::ProtoProject(): Project{"Protoproject"}, starting_task{new Task{"debut"}}, ending_task{new Task{"fin"}}{
		
	this->ending_task->add_dependency(*(this->starting_task));
	this->Project::all_tasks={this->ending_task,this->starting_task};
}

ProtoProject::~ProtoProject(){
	for(Task *t: this->all_tasks){
		delete t;
	}
}

// pour les methodes ci-dessous, je dois respecter l'ordre topologique.
bool ProtoProject::add(const string name, const int duration){
	bool success=false;
	bool depends=true;
	// on ajout d'abord la localisation ici ensuite les depe..
	pair<int,int> ids;
	Task* newTask=new Task{name,duration},*t1=nullptr,*t2=nullptr;
	// t2 ne doit pas dépendre de t1
	int i =0,k=0;
	while(depends){
		ids=this->pick_two_random_tasks();
		
		t1=this->contains(ids.first);
		t2=this->contains(ids.second);
		if(t1!=nullptr && t2!=nullptr){
		depends=t1->depends_from(*t2);
			}
		else{
			depends=true;
		}
	}

	if (IS_PROTO_TESTED) {
		ProtoProject::expected_tsk = newTask;
		ProtoProject::expected_tsk1 = t1;
		ProtoProject::expected_tsk2 = t2;
	}

	newTask->add_dependency(*t2);
	t1->add_dependency(*newTask);

	this->all_tasks.push_back(newTask);

	success=this->topological_sort();
	if(!success){
		this->all_tasks.pop_back();
		for (Task* T:this->all_tasks[i]->getDependencies()){
			if(T==newTask){
				break;
			}
			k++;
		}
		this->all_tasks[i]->remove_dependency(k);
		
		return success;
		}
	return success;
		
}

bool ProtoProject::topological_sort(){
	bool result = this->Project::topological_sort();
	long unsigned int size  = this->all_tasks.size();
	if (result && size > 0){
		this->starting_task =  this->all_tasks[size-1];
		this->ending_task = this->all_tasks[0];
	}
	return result;
}

bool ProtoProject::add(const string name, const int duration, const int dependsID){
// newTask devrait dépendre de la tache ayant comme id dependsID
// et la tache fin devrait dependre de newTask 
	Task* newTask=new Task{name,duration},*t;
	int i;
	bool res=false,found=false;

	t=this->contains(dependsID);// on verfie que l'id recu en prarmètre correespond bien à un tache et on recupère son pointeur 
		
	if(t==nullptr){// si l'id ne correcpond à aucune tache, alors on supprime new task
		delete newTask;
		return res;// et on retourne res qui est = à false
	}

	i=0;
	if (IS_PROTO_TESTED) {
		ProtoProject::expected_tsk = newTask;
	}

	newTask->add_dependency(*t);// on ajoute t(la tache avec l'id dependsID reç en param) au vecteur de dependence de T
	this->ending_task->add_dependency(*newTask);// on ajoute newTask au vecteur de dependence de fin
	this->all_tasks.push_back(newTask);// on insère newTask à la fin du vecteur de toutes les taches du ProtoPorojet
	res=this->topological_sort();// 
	// #tag
	if(!res){// si le tri topologique a échoué
		this->all_tasks.pop_back();// on retire newTask qui est le dernier element de all_tasks
		for (int j=0;j<int (this->all_tasks.size());j++){
		for (Task* T:this->all_tasks[j]->getDependencies()){
			if(T==newTask){// on itère sur les dependences de chaque taches, si on trouve newTask, on arrête
				found=true;
				break;
			}
			i++;// tant qu'on l'a pas trouver on incrément i
			}
			if(found){
			this->all_tasks[j]->remove_dependency(i);// on passe l'indice de newTask dans les dependence 
			i=0;
			found=false;
			}
		}
	}
return res;
}

bool ProtoProject::add(const string name, const int duration , const int idt_avn, const int idt_apn){
	bool res=false,found=false;
	int i=0;
	Task* newTask=new Task{name,duration},*temp=nullptr,*t_av=nullptr,*t_ap=nullptr;
	t_av=this->contains(idt_avn);
	t_ap=this->contains(idt_apn);
	if(t_av == nullptr || t_ap == nullptr){
		// si l'un des deux id ne correspond à aucune tache du vecteur de pointeur de taches all_tasks du projet 
		// on retourne false 
		return res;
	}
	// on verifie si t_av depends de t_ap
	res=t_av->depends_from(*t_ap);
	if(res){// si c'est le cas on verifie si t_ap, depends de t_av
		res=t_ap->depends_from(*t_av);
		if(!res){
			// dans le cas ou t_ap ne depend pas t_av,
			// on dois faire un swap entre t_av et t_ap
			temp=t_av;
			t_av=t_ap;
			t_ap=temp;
		}
		else { // si aucun cas ne nous permet de rajouter la nouvelle tache:
			delete newTask;// on supprime la tache créer dynamiquement
			return false;// on retourne false;
		}
	}

	if (IS_PROTO_TESTED) {
		ProtoProject::expected_tsk = newTask;
	}

	if(!res){

		//ordre de realisation : t_av t t_ap
		newTask->add_dependency(*t_av);// t(newTask) doit avoir dans ses dependence t_av qui doit être réaliser en premier
		t_ap->add_dependency(*newTask);// t_ap doit avoit dans sa liste de dépendence t (newTask)
		this->all_tasks.push_back(newTask);// on ajoute le pointeur de la nouvelle tache dans la fin du vecteur de tache.
		res=this->topological_sort();// on fait le tri topologique
		if(!res)/* si le tri n'est pas réussi, donc il existe un conflit de dépendence*/
		this->all_tasks.pop_back();// on retire newTask du vecteur des pointeur du projet 
		for( int j = 0; j<int(this->all_tasks.size());j++){
		for (Task* T:this->all_tasks[i]->getDependencies()){ // on itère sur les dépendences de chaque tache
			if(T==newTask){// si on rencontre t ( newTask), on doit la supprimer des dépendence
				found=true;
				
				break;// ce mécanisme est fait ainsi afin de corriger les erreurs qui pourr être commise par d'autre méthode 
			}		 // sinon on aurai pu nous limiter juste à t_av et
			i++;// si on a pas rencontrer t ( newTask) on incrémente i
		}
		if(found){
			 this->all_tasks[j]->remove_dependency(i);// remove_dependency(i) verifie l'indice et supprime t (newTask) des dependence de la méthode en question.
			i=0;
			found=false;
		}
	}

	}
	return res;// on retourne enfin res qui est le resultat finale, (si la tache est ajouter ou pas).
}


// get all tasks est une méthode utiliser par la class RunProject pour initiliaser l'ensemble des taches du projet
vector<Task *> ProtoProject::get_all_tasks()const{
	return this->all_tasks;
}
// méthode pour l'affichage
ostream& ProtoProject::afficher(ostream& os)const{
	os<<this->Project::afficher();
    os<<", starting task ["<< this->starting_task->getName() << "("<< this->starting_task->getId() << ")], ";
    os<<", ending task ["<< this->ending_task->getName() << "("<< this->ending_task->getId() << ")]" << endl ;
    return os;
		}
// on a pas besoin de mettre la fonction ci-dessous en tant que friend vu qu'elle utiliser ProtoProject::afficher() qui est publique.
ostream& operator<<(ostream &os,ProtoProject &proto){
	return proto.afficher(os);
}

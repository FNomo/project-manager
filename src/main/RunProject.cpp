#include"Project.hpp"
#include"RunProject.hpp"
#include"ProtoProject.hpp"
#include<sstream>
RunProject::RunProject(const ProtoProject& proto):Project{"RunProject"}{
	this->fill_vector(proto.get_all_tasks());
}

RunProject::~RunProject(){
	for(Task *t: this->all_tasks){
		delete t;
	}
}
// execution est d'une tache qui l'id "@param id" si ses dependence sont toutes déjà executer.
int RunProject::run(int id){
	int result = -1;
	Task *p=nullptr;
	p=this->contains(id);

	if(p!=nullptr && p->isRunnable()){
		p->done();
		result = 0;
	}

	return result;
}
// execute une séquence de tache dans leur ordre sans verifier les dependance et retourne vrai à la fin de l'execution de toute les tache
//@param seq est vecteur d'id de tache.

int RunProject::run(vector<int> seq){
	// int return task curr. state == done sinon -1 en modifiant errno 
	int res=0;
	for(int i : seq){ 
		if (this->run(i) < 0){
			res = -1;
			break;
		}
	}
	return res;
}

//méthode qui sert pour l'affichage 
ostream& RunProject::afficher(ostream& os)const{
	os << this->Project::afficher() << endl;
	return os;
}

ostream& operator<<(ostream &os,RunProject &runn){
	return runn.afficher(os);
}

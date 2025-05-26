# include "Manager.hpp"
# include "Log.hpp"
# include "Util.hpp"

# include <iostream>
# include <sstream>
# include <stdio.h>
using namespace std;


int Manager::ID = 0;


/* ------------------------- *//* ----- Constructeurs ----- *//* ------------------------- */
/* ------------------------- *//* ------------------------- *//* ------------------------- */

/**
 * Construit un manager par défaut
*/
Manager::Manager(string _category): id{ID++}, category{_category}{
	stringstream ss;
	string name;
	ss << this->category << id;
	ss >> name;
	char message[BUFSIZ];
	sprintf(message, "New Manager(%s) %p has been created.", name.c_str(), this);
	Log::d(message);
}

/* ------------------------- *//* ------------------------- *//* ------------------------- */
/* ------------------------- *//* ------------------------- *//* ------------------------- */





/* ------------------------ *//* ----- Destructeurs ----- *//* ------------------------ */
/* ------------------------ *//* ------------------------ *//* ------------------------ */

/**
 * Détruit un manager
*/
Manager::~Manager(){
	char  message[BUFSIZ];
	sprintf(message, "Manager(%s%d) %p has been destructed.", this->category.c_str(), this->id, this);
	Log::d(message);
}

/* ------------------------ *//* ------------------------ *//* ------------------------ */
/* ------------------------ *//* ------------------------ *//* ------------------------ */





/* --------------------- *//* ----- Affichage ----- *//* --------------------- */
/* --------------------- *//* --------------------- *//* --------------------- */

ostream& operator<<(ostream& _out, const Manager& _manager){
	_out << "Manager(" << _manager.id << ") : ";
	_out << "category [" << _manager.category <<"]";

	return _out;
}

/* --------------------- *//* --------------------- *//* --------------------- */
/* --------------------- *//* --------------------- *//* --------------------- */
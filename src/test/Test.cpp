# include "Test.hpp"

# include <iostream>
using namespace std;

int TestSheme::ID = 0;

/* ------------------------- *//* ----- Constructeurs ----- *//* ------------------------- */
/* ------------------------- *//* ------------------------- *//* ------------------------- */

TestSheme::TestSheme(): id{ID++}{}

/**
 * Création d'un shéma de test
 * @param _title le titre du shéma
 * @param _desc la description de test
 * @param _fun la fonction de test
 * @return le shéma crée
*/
TestSheme Test::create_testsheme(string _title, string _desc, test_function _fun){
	TestSheme sheme{};
	sheme.title = _title;
	sheme.description = _desc;
	sheme.fun = _fun;
	return sheme;
}

/* ------------------------- *//* ------------------------- *//* ------------------------- */
/* ------------------------- *//* ------------------------- *//* ------------------------- */





/* --------------------- *//* ----- Lancement ----- *//* --------------------- */
/* --------------------- *//* --------------------- *//* --------------------- */

/**
 * Lance une série de Test sur une liste de shéma
 * @param _test_shemes liste de shéma
*/
void Test::run(vector<TestSheme> _test_shemes){

	for (TestSheme sheme: _test_shemes){
		cout << endl;
		cout << "[" << sheme.title << "] Test " << sheme.id << " starts ..." << endl;
		cout << "[" << sheme.title << "] Test " << sheme.id << " - " << sheme.description << endl;
		sheme.result = (sheme.fun())? SUCCEED: FAILED;
		string result = (sheme.result == SUCCEED)? "succeed": "failed";
		cout << "[" << sheme.title << "] Test " << sheme.id << " Result: " << result << endl;
		cout << endl;
	}

}

/* --------------------- *//* --------------------- *//* --------------------- */
/* --------------------- *//* --------------------- *//* --------------------- */
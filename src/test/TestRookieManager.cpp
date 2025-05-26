# include "TestRookieManager.hpp"
# include "RookieManager.hpp"
# include "ProtoProject.hpp"
# include "RunProject.hpp"
# include "Log.hpp"
# include "Util.hpp"
# include "Task.hpp"

# include <iostream>
# include <vector>
# include <string.h>
using namespace std;

int IS_TESTED = false;
vector<Task*> TestRookieManager::EXPECTED_RESULT = vector<Task*>();

/* --------------------- *//* ----- Les Tests ----- *//* --------------------- */
/* --------------------- *//* --------------------- *//* --------------------- */

/**
 * Lance tous les tests de la classe RookieManager.
*/

void TestRookieManager::run(){
	IS_TESTED = true;
	vector<TestSheme> test_shemes;
	test_shemes.push_back( Test::create_testsheme("Test RookieManager", "Advising with task tree level 0.", TestRookieManager::test0) );
	test_shemes.push_back( Test::create_testsheme("Test RookieManager", "Advising with task tree level 1.", TestRookieManager::test1) );
	test_shemes.push_back( Test::create_testsheme("Test RookieManager", "Advising with task tree level 2.", TestRookieManager::test2) );
	Test::run(test_shemes);
}

/**
 * Teste les conseils d'une jeune conseiller sur un projet facile.
*/
bool TestRookieManager::test0(){
	bool result = true;
	RookieManager manager{};
	ProtoProject p{};
	RunProject project{p};
	Task tsk1{100};

	cout << "--- Before advise() ---" << endl;

	cout << "- Advisor     = " << manager << endl;
	cout << "- Project[0]  = " << tsk1;

	cout << "--- advise() ---" << endl;

	cout << "- Rookie.advise() on Project" << endl;
	TestRookieManager::EXPECTED_RESULT = {&tsk1};
	pair<vector<int>, int> actual = manager.advise(project);

	pair<vector<int>, int> expected;
	expected.first = {tsk1.getId()};
	expected.second = 100;

	char elem[100], content_result[BUFSIZ], content_expected[BUFSIZ];
	memset(elem, 0, 100);
	memset(content_result, 0, BUFSIZ);
	memset(content_expected, 0, BUFSIZ);

	if (expected.first.size() != actual.first.size()) result = false;
	else {
		for (long unsigned int index =0 ; index < expected.first.size(); index++){
			if (expected.first[index] != actual.first[index]){
				result = false;
				break;
			}
		}

		if (expected.second != actual.second) result = false;
	}

	cout << "--- After advise() ---" << endl;

	strcat(content_result, "orders [");
	strcat(content_expected, "orders [");

	for (int num: actual.first){
		if (actual.first.back() != num) sprintf(elem, "%d, ", num);
		else sprintf(elem, "%d", num);
		strcat(content_result, elem);
	}

	for (int num: expected.first){
		if (expected.first.back() != num) sprintf(elem, "%d, ", num);
		else sprintf(elem, "%d", num);
		strcat(content_expected, elem);
	}

	sprintf(elem, "], duration [%d]", actual.second);
	strcat(content_result, elem);
	sprintf(elem, "], duration [%d]", expected.second);
	strcat(content_expected, elem);

	cout << "- Result      = " << content_result << endl;
	cout << "- Expected    = " << content_expected << endl;

	p.all_tasks.clear();
	project.all_tasks.clear();
	return result;
}

/**
 * Teste les conseils d'une jeune conseiller sur un projet moyen.
*/
bool TestRookieManager::test1(){
	bool result = true;
	RookieManager manager{};
	ProtoProject p{};
	RunProject project{p};
	Task tsk1{100};
	Task tsk2{200}, tsk3{200}, tsk4{200};
	vector<Task*> deps = {&tsk2, &tsk3, &tsk4};
	tsk1.set_dependencies(deps);

	cout << "--- Before advise() ---" << endl;

	cout << "- Advisor     = " << manager << endl;
	cout << "- Project[0]  = " << tsk1;
	cout << "- Project[1]  = " << tsk2;
	cout << "- Project[2]  = " << tsk3;
	cout << "- Project[3]  = " << tsk4;

	cout << "--- advise() ---" << endl;

	cout << "- Rookie.advise() on Project" << endl;
	TestRookieManager::EXPECTED_RESULT = {&tsk1, &tsk2, &tsk3, &tsk4};
	pair<vector<int>, int> actual = manager.advise(project);

	pair<vector<int>, int> expected;
	expected.first = {tsk4.getId(), tsk3.getId(), tsk2.getId(), tsk1.getId()};
	expected.second = 700;

	char elem[100], content_result[BUFSIZ], content_expected[BUFSIZ];
	memset(elem, 0, 100);
	memset(content_result, 0, BUFSIZ);
	memset(content_expected, 0, BUFSIZ);

	if (expected.first.size() != actual.first.size()) result = false;
	else {
		for (long unsigned int index =0 ; index < expected.first.size(); index++){
			if (expected.first[index] != actual.first[index]){
				result = false;
				break;
			}
		}

		if (expected.second != actual.second) result = false;
	}

	cout << "--- After advise() ---" << endl;

	strcat(content_result, "orders [");
	strcat(content_expected, "orders [");

	for (int num: actual.first){
		if (actual.first.back() != num) sprintf(elem, "%d, ", num);
		else sprintf(elem, "%d", num);
		strcat(content_result, elem);
	}

	for (int num: expected.first){
		if (expected.first.back() != num) sprintf(elem, "%d, ", num);
		else sprintf(elem, "%d", num);
		strcat(content_expected, elem);
	}

	sprintf(elem, "], duration [%d]", actual.second);
	strcat(content_result, elem);
	sprintf(elem, "], duration [%d]", expected.second);
	strcat(content_expected, elem);

	cout << "- Result      = " << content_result << endl;
	cout << "- Expected    = " << content_expected << endl;

	p.all_tasks.clear();
	project.all_tasks.clear();
	return result;
}

/**
 * Teste les conseils d'une jeune conseiller sur un projet difficile.
*/
bool TestRookieManager::test2(){
	bool result = true;
	RookieManager manager{};
	ProtoProject p{};
	RunProject project{p};
	Task tsk1{100};
	Task tsk2{200}, tsk3{200}, tsk4{200};
	Task tsk5{300}, tsk6{300}, tsk7{300};
	vector<Task*> deps = {&tsk2, &tsk3, &tsk4};
	tsk1.set_dependencies(deps);
	deps = {&tsk5, &tsk6};
	tsk2.set_dependencies(deps);
	deps = {&tsk7};
	tsk3.set_dependencies(deps);

	cout << "--- Before advise() ---" << endl;

	cout << "- Advisor     = " << manager << endl;
	cout << "- Project[0]  = " << tsk1;
	cout << "- Project[1]  = " << tsk2;
	cout << "- Project[2]  = " << tsk3;
	cout << "- Project[3]  = " << tsk4;
	cout << "- Project[4]  = " << tsk5;
	cout << "- Project[5]  = " << tsk6;
	cout << "- Project[6]  = " << tsk7;

	cout << "--- advise() ---" << endl;

	cout << "- Rookie.advise() on Project" << endl;
	TestRookieManager::EXPECTED_RESULT = {&tsk1, &tsk2, &tsk5, &tsk6, &tsk3, &tsk7, &tsk4};
	pair<vector<int>, int> actual = manager.advise(project);

	pair<vector<int>, int> expected;
	expected.first = {tsk4.getId(), tsk7.getId(), tsk3.getId(), tsk6.getId(), tsk5.getId(), tsk2.getId(), tsk1.getId()};
	expected.second = 1600;

	char elem[100], content_result[BUFSIZ], content_expected[BUFSIZ];
	memset(elem, 0, 100);
	memset(content_result, 0, BUFSIZ);
	memset(content_expected, 0, BUFSIZ);

	if (expected.first.size() != actual.first.size()) result = false;
	else {
		for (long unsigned int index =0 ; index < expected.first.size(); index++){
			if (expected.first[index] != actual.first[index]){
				result = false;
				break;
			}
		}

		if (expected.second != actual.second) result = false;
	}

	cout << "--- After advise() ---" << endl;

	strcat(content_result, "orders [");
	strcat(content_expected, "orders [");

	for (int num: actual.first){
		if (actual.first.back() != num) sprintf(elem, "%d, ", num);
		else sprintf(elem, "%d", num);
		strcat(content_result, elem);
	}

	for (int num: expected.first){
		if (expected.first.back() != num) sprintf(elem, "%d, ", num);
		else sprintf(elem, "%d", num);
		strcat(content_expected, elem);
	}

	sprintf(elem, "], duration [%d]", actual.second);
	strcat(content_result, elem);
	sprintf(elem, "], duration [%d]", expected.second);
	strcat(content_expected, elem);

	cout << "- Result      = " << content_result << endl;
	cout << "- Expected    = " << content_expected << endl;

	p.all_tasks.clear();
	project.all_tasks.clear();
	return result;
}

/* --------------------- *//* --------------------- *//* --------------------- */
/* --------------------- *//* --------------------- *//* --------------------- */






/* ---------------------- *//* ----- Principale ----- *//* ---------------------- */
/* ---------------------- *//* ---------------------- *//* ---------------------- */

int main(){
	Log::init();
	TestRookieManager::run();
	Log::close();
	return EXIT_SUCCESS;
}

/* ---------------------- *//* ---------------------- *//* ---------------------- */
/* ---------------------- *//* ---------------------- *//* ---------------------- */
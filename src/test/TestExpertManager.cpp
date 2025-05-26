# include "TestExpertManager.hpp"
# include "ExpertManager.hpp"
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
vector<Task*> TestExpertManager::EXPECTED_RESULT = vector<Task*>();

/* --------------------- *//* ----- Les Tests ----- *//* --------------------- */
/* --------------------- *//* --------------------- *//* --------------------- */

/**
 * Lance tous les tests de la classe ExpertManager.
*/

void TestExpertManager::run(){
	IS_TESTED = true;
	vector<TestSheme> test_shemes;
	test_shemes.push_back( Test::create_testsheme("Test ExpertManager", "Advising with a simple task tree.", TestExpertManager::test0) );
	test_shemes.push_back( Test::create_testsheme("Test ExpertManager", "Advising with a moderate task tree.", TestExpertManager::test1) );
	test_shemes.push_back( Test::create_testsheme("Test ExpertManager", "Advising with a hard task tree.", TestExpertManager::test2) );
	test_shemes.push_back( Test::create_testsheme("Test ExpertManager", "Advising with a extra hard task tree.", TestExpertManager::test3) );
	Test::run(test_shemes);
}

/**
 * Teste les conseils d'une jeune conseiller sur un projet facile.
*/
bool TestExpertManager::test0(){
	bool result = true;
	ExpertManager manager{};
	ProtoProject p{};
	RunProject project{p};
	Task tsk1{100};

	cout << "--- Before advise() ---" << endl;

	cout << "- Advisor     = " << manager << endl;
	cout << "- Project[0]  = " << tsk1;

	cout << "--- advise() ---" << endl;

	cout << "- Expert.advise() on Project" << endl;
	TestExpertManager::EXPECTED_RESULT = {&tsk1};
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
bool TestExpertManager::test1(){
	bool result = true;
	ExpertManager manager{};
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

	cout << "- Expert.advise() on Project" << endl;
	TestExpertManager::EXPECTED_RESULT = {&tsk1, &tsk2, &tsk3, &tsk4};
	pair<vector<int>, int> actual = manager.advise(project);

	pair<vector<int>, int> expected;
	expected.first = {tsk2.getId(), tsk3.getId(), tsk4.getId(), tsk1.getId()};
	expected.second = 300;

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
bool TestExpertManager::test2(){
	bool result = true;
	ExpertManager manager{};
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

	cout << "- Expert.advise() on Project" << endl;
	TestExpertManager::EXPECTED_RESULT = {&tsk1, &tsk2, &tsk5, &tsk6, &tsk3, &tsk7, &tsk4};
	pair<vector<int>, int> actual = manager.advise(project);

	pair<vector<int>, int> expected;
	expected.first = {tsk5.getId(), tsk6.getId(), tsk7.getId(), tsk2.getId(), tsk3.getId(), tsk4.getId(), tsk1.getId()};
	expected.second = 600;

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
 * Teste les conseils d'une jeune conseiller sur un projet ulta complexe.
*/
bool TestExpertManager::test3(){
	bool result = true;
	ExpertManager manager{};
	ProtoProject p{};
	RunProject project{p};
	Task tsk1{100};
	Task tsk2{200}, tsk3{200}, tsk4{200}, tsk5{200}, tsk6{200};
	Task tsk7{300}, tsk8{300}, tsk9{300}, tsk10{300}, tsk11{300}, tsk12{300}, tsk13{300};
	Task tsk14{400}, tsk15{400}, tsk16{400};
	Task tsk17{500};
	vector<Task*> deps = {&tsk2, &tsk3, &tsk4, &tsk5, &tsk6};
	tsk1.set_dependencies(deps);
	deps = {&tsk7, &tsk8, &tsk9};
	tsk2.set_dependencies(deps);
	deps = {&tsk14, &tsk15};
	tsk7.set_dependencies(deps);
	deps = {&tsk10};
	tsk3.set_dependencies(deps);
	deps = {&tsk11};
	tsk5.set_dependencies(deps);
	deps = {&tsk16};
	tsk11.set_dependencies(deps);
	deps = {&tsk17};
	tsk16.set_dependencies(deps);
	deps = {&tsk12, &tsk13};
	tsk6.set_dependencies(deps);
	deps = {&tsk17};
	tsk16.set_dependencies(deps);

	cout << "--- Before advise() ---" << endl;

	cout << "- Advisor     = " << manager << endl;
	cout << "- Project[0]  = " << tsk1;
	cout << "- Project[1]  = " << tsk2;
	cout << "- Project[2]  = " << tsk3;
	cout << "- Project[3]  = " << tsk4;
	cout << "- Project[4]  = " << tsk5;
	cout << "- Project[5]  = " << tsk6;
	cout << "- Project[6]  = " << tsk7;
	cout << "- Project[7]  = " << tsk8;
	cout << "- Project[8]  = " << tsk9;
	cout << "- Project[9]  = " << tsk10;
	cout << "- Project[10]  = " << tsk11;
	cout << "- Project[11]  = " << tsk12;
	cout << "- Project[12]  = " << tsk13;
	cout << "- Project[13]  = " << tsk14;
	cout << "- Project[14]  = " << tsk15;
	cout << "- Project[15]  = " << tsk16;
	cout << "- Project[16]  = " << tsk17;

	cout << "--- advise() ---" << endl;

	cout << "- Expert.advise() on Project" << endl;
	TestExpertManager::EXPECTED_RESULT = {&tsk1, &tsk2, &tsk7, &tsk14, &tsk15, &tsk8, &tsk9, &tsk3, &tsk10, &tsk4, &tsk5, &tsk11, &tsk16, &tsk17, &tsk6, &tsk12, &tsk13};
	pair<vector<int>, int> actual = manager.advise(project);

	pair<vector<int>, int> expected;
	expected.first = {tsk17.getId(), tsk14.getId(), tsk15.getId(), tsk16.getId(), tsk7.getId(), tsk8.getId(),
		tsk9.getId(), tsk10.getId(), tsk11.getId(), tsk12.getId(), tsk13.getId(), tsk2.getId(), tsk3.getId(),
		tsk4.getId(), tsk5.getId(), tsk6.getId(), tsk1.getId()};
	expected.second = 1500;

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
	TestExpertManager::run();
	Log::close();
	return EXIT_SUCCESS;
}

/* ---------------------- *//* ---------------------- *//* ---------------------- */
/* ---------------------- *//* ---------------------- *//* ---------------------- */
# include "TestTask.hpp"
# include "Task.hpp"
# include "Log.hpp"

# include <iostream>
# include <vector>
using namespace std;

/* --------------------- *//* ----- Les Tests ----- *//* --------------------- */
/* --------------------- *//* --------------------- *//* --------------------- */

/**
 * Lance tous les tests de la classe Task.
*/
void TestTask::run(){
	vector<TestSheme> test_shemes;
	test_shemes.push_back( Test::create_testsheme("Test Task", "Completing Task succeed.", TestTask::test0) );
	test_shemes.push_back( Test::create_testsheme("Test Task", "Completing Task failed.", TestTask::test1) );
	test_shemes.push_back( Test::create_testsheme("Test Task", "Asking Dependencies succeed.", TestTask::test2) );
	test_shemes.push_back( Test::create_testsheme("Test Task", "Asking Dependencies failed.", TestTask::test3) );
	test_shemes.push_back( Test::create_testsheme("Test Task", "Adding dependencies succeed.", TestTask::test4) );
	test_shemes.push_back( Test::create_testsheme("Test Task", "Adding dependencies failed.", TestTask::test5) );
	test_shemes.push_back( Test::create_testsheme("Test Task", "Getting Duration of completion.", TestTask::test6) );
	Test::run(test_shemes);
}

/**
 * Teste le succès de la réalisation d'une tâche
*/
bool TestTask::test0(){
	bool res_state = true;
	Task t{}, tsk1{}, tsk2{}, tsk3{}, tsk4{};
	tsk2.set_state(DONE); tsk3.set_state(DONE); tsk4.set_state(DONE);
	vector<Task*> deps = {&tsk2, &tsk3, &tsk4};
	tsk1.set_dependencies(deps);
	Task t_expected{t};
	Task tsk1_expected{tsk1};
	bool code;

	cout << "--- Before done() ---" << endl;

	cout << "- Actual   = " << t;
	cout << "- Actual   = " << tsk1;
	cout << "- Actual   = " << tsk2;
	cout << "- Actual   = " << tsk3;
	cout << "- Actual   = " << tsk4;

	cout << "--- done() ---" << endl;

	code = t.done();
	cout << "- " << t.name << ".done()" << endl;
	t_expected.set_state(DONE);
	res_state = res_state && code && t_expected.state == DONE && t.state == DONE;

	tsk1.done();
	cout << "- " << tsk1.name << ".done()" << endl;
	tsk1_expected.set_state(DONE);
	res_state = res_state && code && tsk1_expected.state == DONE && tsk1.state == DONE;

	cout << "--- After done() ---" << endl;

	cout << "- Actual   = " << t;
	cout << "- Expected = " << t_expected;
	cout << "- Actual   = " << tsk1;
	cout << "- Expected = " << tsk1_expected;


	return res_state;
}

/**
 * Teste le'échec de la réalisation d'une tâche
*/
bool TestTask::test1(){
	bool res_state = true;
	Task tsk{}, tsk1{}, tsk2{};
	vector<Task*> deps = {&tsk1, &tsk2};
	tsk.set_dependencies(deps);
	Task tsk_expected{tsk};
	bool code;

	cout << "--- Before done() ---" << endl;

	cout << "- Actual   = " << tsk;
	cout << "- Actual   = " << tsk1;
	cout << "- Actual   = " << tsk2;

	cout << "--- done() ---" << endl;

	code = tsk.done();
	cout << "- " << tsk.name << ".done()" << endl;
	res_state = res_state && !code && tsk_expected.state == PENDING && tsk.state == PENDING;

	cout << "--- After done() ---" << endl;

	cout << "- Actual   = " << tsk;
	cout << "- Expected = " << tsk_expected;

	return res_state;
}

/**
 * Teste le succès de la dépendance de tâche
*/
bool TestTask::test2(){
	bool res_state = true;
	int code1, code2, code1_expected = true, code2_expected = true;

	Task tsk{}, tsk1{}, tsk2{}, tsk3{}, tsk4{};
	vector<Task*> deps = {&tsk1};
	tsk.set_dependencies(deps);
	deps = {&tsk4};
	tsk3.set_dependencies(deps);
	deps = {&tsk3};
	tsk2.set_dependencies(deps);


	cout << "--- Before depends_from() ---" << endl;

	cout << "- Actual   = " << tsk;
	cout << "- Actual   = " << tsk1;
	cout << "- Actual   = " << tsk2;
	cout << "- Actual   = " << tsk3;
	cout << "- Actual   = " << tsk4;

	cout << "--- depends_from() ---" << endl;

	cout << "- " << tsk.name << ".depends_from(" << tsk1.name <<")" << endl;
	code1 = tsk.depends_from(tsk1);
	res_state = res_state && code1;

	cout << "- " << tsk2.name << ".depends_from(" << tsk4.name <<")" << endl;
	code2 = tsk2.depends_from(tsk4);
	res_state = res_state && code2;


	cout << "--- After depends_from() ---" << endl;

	cout << "- Actual   = " << tsk.name << ((code1)?" depends from ": " don't depends from ") << tsk1.name << endl;
	cout << "- Expected = " << tsk.name << ((code1_expected)?" depends from ": " don't depends from ") << tsk1.name << endl;
	cout << "- Actual   = " << tsk2.name << ((code2)?" depends from ": " don't depends from ") << tsk4.name << endl;
	cout << "- Expected = " << tsk2.name << ((code2_expected)?" depends from ": " don't depends from ") << tsk4.name << endl;

	return true;
}

/**
 * Teste l'échec de la dépendance de tâche
*/
bool TestTask::test3(){
	bool res_state = true;
	int code1, code2, code1_expected = false, code2_expected = false;

	Task tsk{}, tsk1{}, tsk2{}, tsk3{}, tsk4{};
	vector<Task*> deps = {&tsk1};
	tsk.set_dependencies(deps);
	deps = {&tsk4};
	tsk3.set_dependencies(deps);
	deps = {&tsk3};
	tsk2.set_dependencies(deps);


	cout << "--- Before depends_from() ---" << endl;

	cout << "- Actual   = " << tsk;
	cout << "- Actual   = " << tsk1;
	cout << "- Actual   = " << tsk2;
	cout << "- Actual   = " << tsk3;
	cout << "- Actual   = " << tsk4;

	cout << "--- depends_from() ---" << endl;

	cout << "- " << tsk.name << ".depends_from(" << tsk4.name <<")" << endl;
	code1 = tsk.depends_from(tsk4);
	res_state = res_state && code1;

	cout << "- " << tsk2.name << ".depends_from(" << tsk1.name <<")" << endl;
	code2 = tsk2.depends_from(tsk1);
	res_state = res_state && code2;


	cout << "--- After depends_from() ---" << endl;

	cout << "- Actual   = " << tsk.name << ((code1)?" depends from ": " don't depends from ") << tsk4.name << endl;
	cout << "- Expected = " << tsk.name << ((code1_expected)?" depends from ": " don't depends from ") << tsk4.name << endl;
	cout << "- Actual   = " << tsk2.name << ((code2)?" depends from ": " don't depends from ") << tsk1.name << endl;
	cout << "- Expected = " << tsk2.name << ((code2_expected)?" depends from ": " don't depends from ") << tsk1.name << endl;

	return true;
}

/**
 * Teste le succès de l'ajout d'une tâche aux dépendances
*/
bool TestTask::test4(){
	bool res_state = true;
	int code, found = 0;

	Task tsk{}, t1{}, t2{}, t3{};
	Task t_expected{tsk}, t2_expected{t2};
	vector<Task*> deps = {&t1};
	t2.set_dependencies(deps);

	cout << "--- Before add_dependencies() ---" << endl;

	cout << "- Actual   = " << tsk;
	cout << "- Actual   = " << t1;
	cout << "- Actual   = " << t2;
	cout << "- Actual   = " << t3;

	cout << "--- add_dependencies() ---" << endl;

	code = tsk.add_dependency(t1);
	cout << "- " << tsk.name << ".add_dependency("<< t1.name <<")" << endl;
	t_expected.set_dependencies(deps);

	found = 0;
	for (Task *t: tsk.dependencies)
		if (t->id == t1.id)
			found ++;

	res_state = res_state && code && found == 1;

	t2.add_dependency(t3);
	cout << "- " << t2.name << ".add_dependency("<< t3.name <<")" << endl;
	deps = {&t1, &t3};
	t2_expected.set_dependencies(deps);

	found = 0;
	for (Task *t: tsk.dependencies)
		if (t->id == t1.id) 
			found ++;

	res_state = res_state && code && found == 1;

	cout << "--- After add_dependencies() ---" << endl;

	cout << "- Actual   = " << tsk;
	cout << "- Expected = " << t_expected;
	cout << "- Actual   = " << t2;
	cout << "- Expected = " << t2_expected;

	return res_state;
}

/**
 * Teste l'échec de l'ajout d'une tâche aux dépendances
*/
bool TestTask::test5(){
	bool res_state = true;
	int code, found = 0;

	Task tsk{}, tsk1{}, tsk2{}, tsk3{}, tsk4{};
	vector<Task*> deps = {&tsk1};
	tsk.set_dependencies(deps);
	deps = {&tsk4};
	tsk3.set_dependencies(deps);
	deps = {&tsk3};
	tsk2.set_dependencies(deps);
	Task tsk1_expected{tsk1}, tsk4_expected{tsk4};

	cout << "--- Before add_dependencies() ---" << endl;

	cout << "- Actual   = " << tsk;
	cout << "- Actual   = " << tsk1;
	cout << "- Actual   = " << tsk2;
	cout << "- Actual   = " << tsk3;
	cout << "- Actual   = " << tsk4;

	cout << "--- add_dependencies() ---" << endl;

	code = tsk1.add_dependency(tsk);
	cout << "- " << tsk1.name << ".add_dependency("<< tsk.name <<")" << endl;

	found = 0;
	for (Task *t: tsk1.dependencies)
		if (t->id == tsk.id) found ++;

	res_state = res_state && !code && found == 0;

	tsk4.add_dependency(tsk2);
	cout << "- " << tsk4.name << ".add_dependency("<< tsk2.name <<")" << endl;

	found = 0;
	for (Task *t: tsk4.dependencies)
		if (t->id == tsk2.id) found ++;

	res_state = res_state && !code && found == 0;

	cout << "--- After add_dependencies() ---" << endl;

	cout << "- Actual   = " << tsk1;
	cout << "- Expected = " << tsk1_expected;
	cout << "- Actual   = " << tsk4;
	cout << "- Expected = " << tsk4_expected;

	return res_state;
}

/**
 * Teste le renvoie de la durée de réalisation d'une tâche quelquonque
*/
bool TestTask::test6(){
	bool res_state = true;
	int actual1, expected1, actual2, expected2, actual3, expected3;

	Task tsk1{100}, tsk2{100}, tsk7{100};
	Task tsk3{200}, tsk4{200}, tsk5{200}, tsk8{200}, tsk9{200}, tsk10{200};
	Task tsk6{300}, tsk11{300};

	vector<Task*> deps = {&tsk6};
	tsk4.set_dependencies(deps);
	deps = {&tsk3, &tsk4, &tsk5};
	tsk2.set_dependencies(deps);

	deps = {&tsk11};
	tsk9.set_dependencies(deps);
	tsk9.set_state(DONE);
	deps = {&tsk8, &tsk9, &tsk10};
	tsk7.set_dependencies(deps);

	cout << "--- Before paral_duration() ---" << endl;

	cout << "- Actual   = " << tsk1;
	cout << "- Actual   = " << tsk2;
	cout << "- Actual   = " << tsk3;
	cout << "- Actual   = " << tsk4;
	cout << "- Actual   = " << tsk5;
	cout << "- Actual   = " << tsk6;
	cout << "- Actual   = " << tsk7;
	cout << "- Actual   = " << tsk8;
	cout << "- Actual   = " << tsk9;
	cout << "- Actual   = " << tsk10;
	cout << "- Actual   = " << tsk11;

	cout << "--- paral_duration() ---" << endl;

	actual1 = tsk1.paral_duration(); expected1 = 100;
	res_state = res_state && expected1 == actual1;
	cout << "- " << tsk1.name << ".paral_duration()" << endl;

	actual2 = tsk2.paral_duration(); expected2 = 600;
	res_state = res_state && expected2 == actual2;
	cout << "- " << tsk2.name << ".paral_duration()" << endl;

	actual3 = tsk7.paral_duration(); expected3 = 300;
	res_state = res_state && expected3 == actual3;
	cout << "- " << tsk7.name << ".paral_duration()" << endl;

	cout << "--- After paral_duration() ---" << endl;

	cout << "- Actual   = duration parralel of " << tsk1.name << " is " << actual1 << endl;
	cout << "- Expected = duration parralel of " << tsk1.name << " is " << expected1 << endl;
	cout << "- Actual   = duration parralel of " << tsk1.name << " is " << actual2 << endl;
	cout << "- Expected = duration parralel of " << tsk1.name << " is " << expected2 << endl;
	cout << "- Actual   = duration parralel of " << tsk1.name << " is " << actual3 << endl;
	cout << "- Expected = duration parralel of " << tsk1.name << " is " << expected3 << endl;

	return res_state;
}

/* --------------------- *//* --------------------- *//* --------------------- */
/* --------------------- *//* --------------------- *//* --------------------- */





/* ---------------------- *//* ----- Principale ----- *//* ---------------------- */
/* ---------------------- *//* ---------------------- *//* ---------------------- */

int main(){
	Log::init();
	TestTask::run();
	Log::close();
	return EXIT_SUCCESS;
}

/* ---------------------- *//* ---------------------- *//* ---------------------- */
/* ---------------------- *//* ---------------------- *//* ---------------------- */
#include "TestProtoProject.hpp"
#include "Project.hpp"
#include "ProtoProject.hpp"
#include "Log.hpp"
#include "Task.hpp"
#include <iostream>
#include <vector>

using namespace std;

bool TestProtoProject::test0(){
    // test de creation 
    ProtoProject aProtoP, eProtoP;
    int result=true, code;

    Task task1{},task2{},task3{},task4{},task5{},task6{},task7{};
    vector<Task*> deps={&task2,&task3,&task4};
    task1.set_dependencies(deps);
    deps={&task5,&task6};
    task2.set_dependencies(deps);
    deps={&task7};
    task3.set_dependencies(deps);

	aProtoP.starting_task = &task1;
	aProtoP.ending_task = &task7;
    aProtoP.all_tasks={&task1, &task2, &task3, &task4, &task5, &task6, &task7};
	eProtoP.starting_task = &task5;
	eProtoP.ending_task = &task1;
	eProtoP.all_tasks={&task1, &task4, &task3, &task7, &task2, &task6, &task5};

	/**	 l'arborescence des dependance 
	 *			  __t6__
	 *			 /   |  \
	 *		_(t1)   (t8) (t9)
	 *		/ |	   \
	 *	(t10) (t11)   (t12)
	 * 
	*/
   
	cout << "--- Before sort() ---" << endl;
	int index = 1;
	for (Task *t: aProtoP.all_tasks)
		cout << "- Task" << index++ <<": " << *t;
	cout << "- Project: " << aProtoP;

	code = aProtoP.topological_sort();

	cout << "--- After sort() ---" << endl;
	cout << "- Actual    = " << aProtoP;
	cout << "- Experted  = " << eProtoP;

	if (aProtoP.all_tasks.size() != eProtoP.all_tasks.size()) result = false;
	else {
		for (long unsigned int index =0; index < aProtoP.all_tasks.size(); index++)
			if (aProtoP.all_tasks[index]->getId() != eProtoP.all_tasks[index]->getId()){
				result = false;
				break;
			}
		result = result && code;
		result = result && aProtoP.starting_task->getId() == eProtoP.starting_task->getId();
		result = result && aProtoP.ending_task->getId() == eProtoP.ending_task->getId();
	}
	aProtoP.all_tasks.clear();
    eProtoP.all_tasks.clear();
	return result;
}

bool TestProtoProject::test1(){
    // test de creation 
    ProtoProject aProtoP, eProtoP;
    int result=true, code;

    Task task1{100};
	Task task2{200}, task3{200}, task4{200}, task5{200}, task6{200};
	Task task7{300}, task8{300}, task9{300}, task10{300}, task11{300}, task12{300}, task13{300};
	Task task14{400}, task15{400}, task16{400};
	Task task17{500};
	vector<Task*> deps = {&task2, &task3, &task4, &task5, &task6};
	task1.set_dependencies(deps);
	deps = {&task7, &task8, &task9};
	task2.set_dependencies(deps);
	deps = {&task14, &task15};
	task7.set_dependencies(deps);
	deps = {&task10};
	task3.set_dependencies(deps);
	deps = {&task11};
	task5.set_dependencies(deps);
	deps = {&task16};
	task11.set_dependencies(deps);
	deps = {&task17};
	task16.set_dependencies(deps);
	deps = {&task12, &task13};
	task6.set_dependencies(deps);
	deps = {&task17};
	task16.set_dependencies(deps);

	aProtoP.starting_task = &task1;
	aProtoP.ending_task = &task7;
    aProtoP.all_tasks={&task1, &task2, &task3, &task4, &task5, &task6, &task7, &task8, &task9, &task10, &task11, &task12, &task13, &task14, &task15, &task16, &task17};
	eProtoP.starting_task = &task14;
	eProtoP.ending_task = &task1;
	eProtoP.all_tasks={&task1, &task6, &task13, &task12, &task5, &task11, &task16, &task17, &task4, &task3, &task10, &task2, &task9, &task8, &task7, &task15, &task14};
   
	cout << "--- Before sort() ---" << endl;

	int index = 1;
	for (Task *t: aProtoP.all_tasks)
		cout << "- Task" << index++ <<": " << *t;
	cout << "- Project: " << aProtoP;

	code = aProtoP.topological_sort();

	cout << "--- After sort() ---" << endl;
	cout << "- Actual    = " << aProtoP;
	cout << "- Experted  = " << eProtoP;

	if (aProtoP.all_tasks.size() != eProtoP.all_tasks.size()) result = false;
	else {
		for (long unsigned int index =0; index < aProtoP.all_tasks.size(); index++)
			if (aProtoP.all_tasks[index]->getId() != eProtoP.all_tasks[index]->getId()){
				result = false;
				break;
			}
		result = result && code;
		result = result && aProtoP.starting_task->getId() == eProtoP.starting_task->getId();
		result = result && aProtoP.ending_task->getId() == eProtoP.ending_task->getId();
	}
	aProtoP.all_tasks.clear();
    eProtoP.all_tasks.clear();
	return result;
}

/**
 * Test l'ajout d'une tâche dans le protoprojet
*/
bool TestProtoProject::test2(){
	ProtoProject aProtoP;
	int result=true, code;

    Task task1{100};
	Task task2{200}, task3{200}, task4{200}, task5{200}, task6{200};
	Task task7{300}, task8{300}, task9{300}, task10{300}, task11{300}, task12{300}, task13{300};
	Task task14{400}, task15{400}, task16{400};
	Task task17{500};
	vector<Task*> deps = {&task2, &task3, &task4, &task5, &task6};
	task1.set_dependencies(deps);
	deps = {&task7, &task8, &task9};
	task2.set_dependencies(deps);
	deps = {&task14, &task15};
	task7.set_dependencies(deps);
	deps = {&task10};
	task3.set_dependencies(deps);
	deps = {&task11};
	task5.set_dependencies(deps);
	deps = {&task16};
	task11.set_dependencies(deps);
	deps = {&task17};
	task16.set_dependencies(deps);
	deps = {&task12, &task13};
	task6.set_dependencies(deps);
	deps = {&task17};
	task16.set_dependencies(deps);

	aProtoP.starting_task = &task14;
	aProtoP.ending_task = &task1;
	aProtoP.all_tasks={&task1, &task6, &task13, &task12, &task5, &task11, &task16, &task17, &task4, &task3, &task10, &task2, &task9, &task8, &task7, &task15, &task14};

	cout << "--- Before add(TestTask, 900) ---" << endl;
	int index = 1;
	for (Task *t: aProtoP.all_tasks)
		cout << "- Task" << index++ <<": " << *t;
	cout << "- Project: " << aProtoP;

	code = aProtoP.add("TestTask", 900);
	result = result && code && aProtoP.all_tasks.size() == 18;

	cout << "--- After add(TestTask, 900) ---" << endl;
	index = 1;
	for (Task *t: aProtoP.all_tasks)
		cout << "- Task" << index++ <<": " << *t;
	cout << "- Project: " << aProtoP;

	cout << "--- Result ---" << endl;
	Task* expected_tsk = ProtoProject::expected_tsk;
	Task* expected_tsk1 = ProtoProject::expected_tsk1;
	Task* expected_tsk2 = ProtoProject::expected_tsk2;
	if (expected_tsk != nullptr && expected_tsk1 != nullptr && expected_tsk2 != nullptr){
		code = expected_tsk1->depends_from(*expected_tsk);
		result = result && code;
		cout << "- Actual    = " << expected_tsk1->name << ((code)? " depends from ": " don't depends from ") << expected_tsk->name << endl;
		cout << "- Expected  = " << expected_tsk1->name << " depends from " << expected_tsk->name << endl;
		code = expected_tsk->depends_from(*expected_tsk2);
		result = result && code;
		cout << "- Actual    = " << expected_tsk->name << ((code)? " depends from ": " don't depends from ") << expected_tsk2->name << endl;
		cout << "- Expected  = " << expected_tsk->name << " depends from " << expected_tsk2->name << endl;
	} else result = false;
	aProtoP.all_tasks.clear();
	return result;
}

/**
 * Test l'ajout d'une tâche dans le protoprojet
*/
bool TestProtoProject::test3(){
	ProtoProject aProtoP;
	int result=true, code;

    Task task1{100};
	Task task2{200}, task3{200}, task4{200}, task5{200}, task6{200};
	Task task7{300}, task8{300}, task9{300}, task10{300}, task11{300}, task12{300}, task13{300};
	Task task14{400}, task15{400}, task16{400};
	Task task17{500};
	vector<Task*> deps = {&task2, &task3, &task4, &task5, &task6};
	task1.set_dependencies(deps);
	deps = {&task7, &task8, &task9};
	task2.set_dependencies(deps);
	deps = {&task14, &task15};
	task7.set_dependencies(deps);
	deps = {&task10};
	task3.set_dependencies(deps);
	deps = {&task11};
	task5.set_dependencies(deps);
	deps = {&task16};
	task11.set_dependencies(deps);
	deps = {&task17};
	task16.set_dependencies(deps);
	deps = {&task12, &task13};
	task6.set_dependencies(deps);
	deps = {&task17};
	task16.set_dependencies(deps);

	aProtoP.starting_task = &task14;
	aProtoP.ending_task = &task1;
	aProtoP.all_tasks={&task1, &task6, &task13, &task12, &task5, &task11, &task16, &task17, &task4, &task3, &task10, &task2, &task9, &task8, &task7, &task15, &task14};

	cout << "--- Before add(TestTask, 900, Task17) ---" << endl;
	int index = 1;
	for (Task *t: aProtoP.all_tasks)
		cout << "- Task" << index++ <<": " << *t;
	cout << "- Project: " << aProtoP;

	code = aProtoP.add("TestTask", 900, task17.getId());
	result = result && code && aProtoP.all_tasks.size() == 18;

	cout << "--- After add(TestTask, 900, Task17) ---" << endl;
	index = 1;
	for (Task *t: aProtoP.all_tasks)
		cout << "- Task" << index++ <<": " << *t;
	cout << "- Project: " << aProtoP;

	cout << "--- Result ---" << endl;
	Task* expected_tsk = ProtoProject::expected_tsk;
	if (expected_tsk != nullptr){
		code = expected_tsk->depends_from(task17);
		result = result && code;
		cout << "- Actual    = " << expected_tsk->name << ((code)? " depends from ": " don't depends from ") << task17.name << endl;
		cout << "- Expected  = " << expected_tsk->name << " depends from " << task17.name << endl;
		code = aProtoP.ending_task->depends_from(*expected_tsk);
		result = result && code;
		cout << "- Actual    = " << aProtoP.ending_task->name << ((code)? " depends from ": " don't depends from ") << expected_tsk->name << endl;
		cout << "- Expected  = " << aProtoP.ending_task->name << " depends from " << expected_tsk->name << endl;
	} else result = false;

	aProtoP.all_tasks.clear();
	return result;
}

/**
 * Test l'ajout d'une tâche dans le protoprojet
*/
bool TestProtoProject::test4(){
	ProtoProject aProtoP;
	int result=true, code;

    Task task1{100};
	Task task2{200}, task3{200}, task4{200}, task5{200}, task6{200};
	Task task7{300}, task8{300}, task9{300}, task10{300}, task11{300}, task12{300}, task13{300};
	Task task14{400}, task15{400}, task16{400};
	Task task17{500};
	vector<Task*> deps = {&task2, &task3, &task4, &task5, &task6};
	task1.set_dependencies(deps);
	deps = {&task7, &task8, &task9};
	task2.set_dependencies(deps);
	deps = {&task14, &task15};
	task7.set_dependencies(deps);
	deps = {&task10};
	task3.set_dependencies(deps);
	deps = {&task11};
	task5.set_dependencies(deps);
	deps = {&task16};
	task11.set_dependencies(deps);
	deps = {&task17};
	task16.set_dependencies(deps);
	deps = {&task12, &task13};
	task6.set_dependencies(deps);
	deps = {&task17};
	task16.set_dependencies(deps);

	aProtoP.starting_task = &task14;
	aProtoP.ending_task = &task1;
	aProtoP.all_tasks={&task1, &task6, &task13, &task12, &task5, &task11, &task16, &task17, &task4, &task3, &task10, &task2, &task9, &task8, &task7, &task15, &task14};

	cout << "--- Before add(name, duration) ---" << endl;
	int index = 1;
	for (Task *t: aProtoP.all_tasks)
		cout << "- Task" << index++ <<": " << *t;
	cout << "- Project: " << aProtoP;

	code = aProtoP.add("TestTask", 900, task11.getId(), task16.getId());
	result = result && code && aProtoP.all_tasks.size() == 18;

	cout << "--- After add(name, duration) ---" << endl;
	index = 1;
	for (Task *t: aProtoP.all_tasks)
		cout << "- Task" << index++ <<": " << *t;
	cout << "- Project: " << aProtoP;

	Task* expected_tsk = ProtoProject::expected_tsk;
	if (expected_tsk != nullptr){
		code = task11.depends_from(*expected_tsk);
		result = result && code;
		cout << "- Actual    = " << task11.name << ((code)? " depends from ": " don't depends from ") << expected_tsk->name << endl;
		cout << "- Expected  = " << task11.name << " depends from " << expected_tsk->name << endl;
		code = expected_tsk->depends_from(task16);
		result = result && code;
		cout << "- Actual    = " << expected_tsk->name << ((code)? " depends from ": " don't depends from ") << task16.name << endl;
		cout << "- Expected  = " << expected_tsk->name << " depends from " << task16.name << endl;
	} else result = false;

	aProtoP.all_tasks.clear();
	return result;
}

void TestProtoProject::run(){
	IS_PROTO_TESTED = true;
	vector<TestSheme> test_shemes;
	test_shemes.push_back(Test::create_testsheme("Test ProtoProject","Sorting ProtoProject tasks on hard sheme.",TestProtoProject::test0));
	test_shemes.push_back(Test::create_testsheme("Test ProtoProject","Sorting ProtoProject tasks on extreme sheme.",TestProtoProject::test1));
	test_shemes.push_back(Test::create_testsheme("Test ProtoProject","Adding task between two random Tasks.",TestProtoProject::test2));
	test_shemes.push_back(Test::create_testsheme("Test ProtoProject","Adding task after a Tasks.",TestProtoProject::test3));
	test_shemes.push_back(Test::create_testsheme("Test ProtoProject","Adding task between two Tasks.",TestProtoProject::test4));
	Test::run(test_shemes);
}

int main (){
	Log::init();
	TestProtoProject::run();
	Log::close();
	return EXIT_SUCCESS;
}

# include "TestRunProject.hpp"
# include "Project.hpp"
# include "RunProject.hpp"
# include "ProtoProject.hpp"
# include "Log.hpp"
# include "Task.hpp"
# include <iostream>
# include <vector>
using namespace std;

void TestRunProject::run(){
	IS_PROTO_TESTED = true;
	vector<TestSheme> test_shemes;
	test_shemes.push_back(Test::create_testsheme("Test RunProject","Running one Task on RunProject.",TestRunProject::test0));
	test_shemes.push_back(Test::create_testsheme("Test RunProject","Running list of Task on RunProject.",TestRunProject::test1));
	Test::run(test_shemes);
}

bool TestRunProject::test0(){
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
	RunProject aRunP{aProtoP};

	cout << "--- Before run(Task15) ---" << endl;
	int index = 1;
	cout << "- Project: " << aRunP;
	for (Task *t: aProtoP.all_tasks)
		cout << "- Task" << index++ <<": " << *t;

	code = aRunP.run(task15.getId());
	result = result && code == 0 && task15.state == DONE;
	for (Task *t: aRunP.all_tasks){
		if (t->id != task15.id && t->state == DONE){
			result = false;
			break;
		}
	}

	cout << "--- After run(Task15) ---" << endl;
	index = 1;
	cout << "- Project: " << aRunP;
	for (Task *t: aProtoP.all_tasks)
		cout << "- Task" << index++ <<": " << *t;

	aProtoP.all_tasks.clear();
	aRunP.all_tasks.clear();

	return result;
}

bool TestRunProject::test1(){
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
	RunProject aRunP{aProtoP};
	vector<int> orders = {task17.id, task14.id, task15.id, task16.id, task7.id,
		task8.id, task9.id, task10.id, task11.id, task12.id, task13.id, task2.id,
		task3.id, task4.id, task5.id, task6.id, task1.id};

	cout << "--- Before run(orders) ---" << endl;
	int index = 1;
	cout << "- Project: " << aRunP;
	for (Task *t: aProtoP.all_tasks)
		cout << "- Task" << index++ <<": " << *t;

	cout << "- Expected orders [";
	for (int id: orders){
		cout << id;
		if (id != orders.back()) cout << ", ";
	}
	cout << "]" << endl;

	code = aRunP.run(orders);
	result = result && code == 0;
	if (result){
		for (Task *t: aRunP.all_tasks){
			if (t->state != DONE) {
				result = false;
				break;
			}
		}
	}

	cout << "--- After run(orders) ---" << endl;
	index = 1;
	cout << "- Project: " << aRunP;
	for (Task *t: aProtoP.all_tasks)
		cout << "- Task" << index++ <<": " << *t;

	aProtoP.all_tasks.clear();
	aRunP.all_tasks.clear();

	return result;
}

int main (){
	Log::init();
	TestRunProject::run();
	Log::close();
	return EXIT_SUCCESS;
}
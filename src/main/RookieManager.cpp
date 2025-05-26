# include "RookieManager.hpp"
# include "RunProject.hpp"
# include "TestRookieManager.hpp"
# include "Task.hpp"
# include "Log.hpp"
# include "Util.hpp"

# include <iostream>
# include <vector>
# include <algorithm>
using namespace std;

/* ------------------------- *//* ----- Constructeurs ----- *//* ------------------------- */
/* ------------------------- *//* ------------------------- *//* ------------------------- */

RookieManager::RookieManager():Manager{"Rookie"}{}

/* ------------------------- *//* ------------------------- *//* ------------------------- */
/* ------------------------- *//* ------------------------- *//* ------------------------- */





/* -------------------- *//* ----- Conseils ----- *//* -------------------- */
/* -------------------- *//* -------------------- *//* -------------------- */

/**
 * Recommendations de l'ordre dans lequel doit être éffectuer les tâches et la durée totale à prévoir sur un projet donné.
 * @param _project le projet à évaluer
 * @return une pair contenant l'ordre des tâche et la durée nécéssaire pour toute les éffectuer
*/
pair<vector<int>, int> RookieManager::advise(const RunProject& _project){
	pair<vector<int>, int> result;
	const vector<Task*> tasks = (IS_TESTED)? TestRookieManager::EXPECTED_RESULT: _project.consult_tasks();
	vector<int> task_order{};
	int global_duration = 0;
	
	for (Task *tsk: tasks)
		if (!tsk->isDone()){
			task_order.push_back(tsk->getId());
			global_duration += tsk->getDuration();
		}
		
	reverse(task_order.begin(), task_order.end());


	result.first = task_order; result.second = global_duration;
	return result;
}

/* -------------------- *//* -------------------- *//* -------------------- */
/* -------------------- *//* -------------------- *//* -------------------- */
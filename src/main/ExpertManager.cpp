# include "ExpertManager.hpp"
# include "TestExpertManager.hpp"
# include "RunProject.hpp"
# include "Task.hpp"
# include "Log.hpp"
# include "Util.hpp"

# include <iostream>
# include <vector>
# include <algorithm>
using namespace std;

/* ------------------------- *//* ----- Constructeurs ----- *//* ------------------------- */
/* ------------------------- *//* ------------------------- *//* ------------------------- */

ExpertManager::ExpertManager(): Manager{"Expert"}{}

/* ------------------------- *//* ------------------------- *//* ------------------------- */
/* ------------------------- *//* ------------------------- *//* ------------------------- */





/* -------------------- *//* ----- Conseils ----- *//* -------------------- */
/* -------------------- *//* -------------------- *//* -------------------- */

/**
 * Recommendations de l'ordre dans lequel doit être éffectuer les tâches et la durée totale à prévoir sur un projet donné.
 * @param _project le projet à évaluer
 * @return une pair contenant l'ordre des tâche et la durée nécéssaire pour toute les éffectuer
*/
pair<vector<int>, int> ExpertManager::advise(const RunProject& _project){
	pair<vector<int>, int> result;
	const vector<Task*> tasks = (IS_TESTED)? TestExpertManager::EXPECTED_RESULT: _project.consult_tasks();

	vector<Task*> task_with_levels[100];
	for (int index=0; index < 100; index++) task_with_levels[index] = vector<Task*>();
	unsigned int level = 0;

	for (Task *t: tasks){
		

		while(level >= 0){
			if (task_with_levels[0].size() < 1 ){
				task_with_levels[level].push_back(t);
				break;
			}

			else if (task_with_levels[level].back()->depends_from(*t) ) {
				level++;
				task_with_levels[level].push_back(t);
				break;
			}

			level--;
		}

		
	}

	result.first = vector<int>();
	Task *last = nullptr;
	for (int index = 99; index >=0; index--){
		for (Task *t: task_with_levels[index]) {
			result.first.push_back(t->getId());
			last = t;
		}
	}
	
	result.second = -1;
	if (last != nullptr) {
		result.second = last->paral_duration();
	}
	return result;
}

/* -------------------- *//* -------------------- *//* -------------------- */
/* -------------------- *//* -------------------- *//* -------------------- */
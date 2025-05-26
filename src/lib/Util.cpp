# include "Util.hpp"

# include <iostream>
# include <vector>
# include <errno.h>
using namespace std;

/**
 * Obtenir la valeur maximal d'une séquence d'entier
 * @param _list liste d'entier
 * @return la valeur maxiimale ou -1 en changeant `errno` si erreur
*/
int Util::max(vector<int> _list){
	if (_list.size() == 0){
		errno = EINVAL;
		return -1;
	}

	int max = _list[0];
	for (int val: _list)
		if (val > max) max = val;
	
	return max;
}
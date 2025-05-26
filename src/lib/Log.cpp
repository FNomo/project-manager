# include "Log.hpp"

# include <iostream>
# include <vector>
# include <errno.h>
# include <sys/types.h>
# include <dirent.h>
# include <time.h>
# include <sys/time.h>
#include <string.h>
using namespace std;

vector<string> Log::CONTEXTS = {"Main"} ;
ofstream Log::LOG_STREAM = ofstream();

/**
 * Inialise l'affiche de Débuggage
 * * Vérifie l'existance du répertoire `log/`.
 * * Crée un fichier de debuggage dans ce répertoire
 * @return 0 en cas de succes ou -1 en modifiant `errno` en cas d'erreur
*/
int Log::init(){
	DIR *dir;
	
	if ((dir = opendir ("log")) == NULL) {
		errno  = ENOENT;
		return -1;
	}
	
	struct dirent *ent;
	int count_of_file = 0;
	while ((ent = readdir (dir)) != NULL) {
		count_of_file++;
	}
	count_of_file -=2;

	closedir (dir);

	time_t t= time(NULL);
	struct tm* now = localtime(&t);
	char fname[BUFSIZ];

	if (count_of_file == 0) sprintf(fname, "log/ProgramTrace[%.04d-%.02d-%.02d].log", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
	else sprintf(fname, "log/ProgramTrace[%.04d-%.02d-%.02d](%d).log", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, count_of_file);

	LOG_STREAM.open(fname, ios::trunc);
	if (!LOG_STREAM.is_open()) return -1;
	return 0;
}

/**
 * Termine le debuggage
*/
void Log::close(){
	
}

/**
 * Ajoute un nouveau context de debuggage
 * @param _new_context le contexte à ajoute
*/
void Log::add_context(string _new_context){
	if (_new_context.size() > 11){
		errno = EINVAL;
		return;
	}
	CONTEXTS.push_back(_new_context);
}

/**
 * Supprime le dernier context ajouté
*/
void Log::remove_context(){
	CONTEXTS.pop_back();
}

/*
 * Ecrit un message dans le fichier de débugage en tenant compte du mode
 * @param _mode le mode à préciser
 * @param _message le message à écrire
 */
void Log::print(string _mode, string _message){
	if (!LOG_STREAM.is_open()) return;
	string mode = "[" + _mode + "]";
	char time_field[100] , context_field[100], mode_field[100];
	memset(time_field, 0, 100);
	memset(context_field, 0, 100);
	memset(mode_field, 0, 100);

	struct timeval tv;
	gettimeofday(&tv,NULL);
	struct tm *now = localtime(&tv.tv_sec);

	sprintf(time_field, "%.02d:%.02d:%.02d.%.06ld     ", now->tm_hour, now->tm_min, now->tm_sec, tv.tv_usec);
	sprintf(context_field,"%-15s", CONTEXTS.back().c_str());
	sprintf(mode_field,"%-15s",mode.c_str());

	LOG_STREAM << time_field << context_field << mode_field << _message << endl ;
}

/**
 * Ecrit un debuggage dans le fichier de log
 * @param _message le message à écrire
*/
void Log::d(string _message){
	Log::print("DEBUG", _message);
}

/**
 * Ecrit une erreur dans le fichier de log
 * @param _message le message à écrire
*/
void Log::e(string _message){
	Log::print("ERROR", _message);
}

/**
 * Ecrit une verbose dans le fichier de log
 * @param _message le message à écrire
*/
void Log::v(string _message){
	Log::print("VERBOSE", _message);
}

/**
 * Ecrit une information dans le fichier de log
 * @param _message le message à écrire
*/
void Log::i(string _message){
	Log::print("INFO", _message);
}


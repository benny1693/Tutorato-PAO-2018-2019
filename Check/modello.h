#ifndef MODELLO_H
#define MODELLO_H

#include<fstream>
#include "todo.h"
#include<list>

using std::list;

class Modello
{
private:
	list<ToDo*> lista;
public:
	Modello();
	~Modello();

	void add(string);
	void remove(string);
	void save(string) const;
};

#endif // MODELLO_H

#include "modello.h"

Modello::Modello() {}

Modello::~Modello() {
	for (list<ToDo *>::iterator it = lista.begin(); it != lista.end(); it++)
		delete *it;
}

// Metodo per aggiungere un elemento di nome el
void Modello::add(string el) { lista.push_back(new ToDo(el)); }

// Metodo per togliere un elemento di nome el
void Modello::remove(string el) {

	list<ToDo *>::iterator it = lista.begin();

	while (it != lista.end() && **it != ToDo(el))
		it++;

	if (it != lista.end()) {
		delete *it;
		lista.erase(it);
	}
}

// Metodo di salvataggio della lista nel file indicato
void Modello::save(string path) const {

	std::ofstream file;
	file.open(path);

	for (list<ToDo *>::const_iterator it = lista.begin(); it != lista.end(); it++)
		file << **it << std::endl;

	file.close();
}

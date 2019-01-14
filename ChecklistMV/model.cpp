#include "model.h"
#include "todo.h"
#include "xmlio.h"

#include <QtAlgorithms> // per qDeleteAll

Model::Model() {}

Model::~Model() {
    qDeleteAll(list); // cancella tutti i puntatori contenuti nella QList
}

// Metodo di salvataggio della lista nel file indicato
void Model::saveToFile() const {
    XmlIO xmlio("../ChecklistMV/data/data.xml");
    xmlio.write(list);
}

void Model::loadFromFile() {
    XmlIO xmlio("../ChecklistMV/data/data.xml");
    list = xmlio.read();
}

int Model::todoCount() const {
    return list.size();
}
/*
 * Ritorna il Todo in posizione 'index'
 */
const Todo* Model::getTodo(int index) const {
    return list.at(index);
}

void Model::add(Todo* todo) {
    list.append(todo);
}

void Model::remove(int index) {
    delete list[index];
    list.removeAt(index);
}

void Model::replace(int index, Todo* todo) {
    delete list.at(index);
    list.replace(index, todo);
}

void Model::editTodo(int index, const string& text) {
    list[index]->editValue(text);
}

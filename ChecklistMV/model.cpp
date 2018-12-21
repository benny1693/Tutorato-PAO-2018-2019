#include "model.h"
#include "todo.h"
#include "xmlio.h"

#include <QtAlgorithms>

Model::Model() {}

Model::~Model() {
    qDeleteAll(list); // cancella tutti i puntatori contenuti nella QList
}

// Metodo di salvataggio della lista nel file indicato
void Model::saveToFile(string filename) const {
    XmlIO xmlio("../ChecklistMV/data/" + QString::fromStdString(filename) + ".xml");
    xmlio.write(list);
}

void Model::loadFromFile(string filename) {
    XmlIO xmlio("../ChecklistMV/data/" + QString::fromStdString(filename) + ".xml");
    list = xmlio.read();
}

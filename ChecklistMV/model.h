#ifndef MODELLO_H
#define MODELLO_H

#include <QList>

class Todo;

using std::string;

class Model {
private:
    QList<Todo*> list;
public:
    Model();
    ~Model();

    // Faremo le funzionalità di aggiunta e rimozione usando il pattern Model/View di Qt

    void saveToFile(string) const;
    void loadFromFile(string);
};

#endif // MODELLO_H

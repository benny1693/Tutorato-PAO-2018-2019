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

    void saveToFile() const;
    void loadFromFile();
    int todoCount() const;

    void add(Todo*); // aggiunge un Todo alla lista
    void remove(int); // rimuove il Todo di indice 'index'
    void replace(int, Todo*); // sostituisce il Todo di indice specificato con un altro
    const Todo* getTodo(int) const; // ritorna il Todo di indice specificato
    void editTodo(int, const string&);
};

#endif // MODELLO_H

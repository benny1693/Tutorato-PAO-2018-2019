#ifndef SPECIALTODO_H
#define SPECIALTODO_H

#include "todo.h"

#include <string>

class SpecialTodo : public Todo { // sottoclasse un po' forzata (bastava un booleano in Todo)
public:
    SpecialTodo(string = "");

    string getType() const override;
};

#endif // SPECIALTODO_H

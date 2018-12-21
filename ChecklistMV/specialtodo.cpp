#include "specialtodo.h"

SpecialTodo::SpecialTodo(string text) : Todo(text) {}

string SpecialTodo::getType() const {
    return "special";
}

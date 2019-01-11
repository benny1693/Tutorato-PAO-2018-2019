#include "todo.h"

Todo::Todo(string text) : text(text) {}

string Todo::getText() const {
    return text;
}

string Todo::getType() const {
    return "standard";
}

void Todo::editValue(string val) {
    text = val;
}

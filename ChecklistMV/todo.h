#ifndef TODO_H
#define TODO_H

#include <string>

using std::string;

class Todo {
protected:
	string text;

public:
    Todo(string = "");
    virtual ~Todo() = default;

    virtual string getText() const;
    virtual string getType() const;
    void editValue(string);
};

#endif // TODO_H

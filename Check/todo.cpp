#include "todo.h"

std::ostream& operator<<(std::ostream& out,
												 const ToDo& t)
{
	out << t.text;
	return out;
}

ToDo::ToDo(string t) : text(t) {}

bool ToDo::operator==(const ToDo &t) const {
	return text == t.text;
}

bool ToDo::operator!=(const ToDo & t) const {
	return !(*this == t);
}

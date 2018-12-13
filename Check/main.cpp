#include "check.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Check w;
	w.show();

	return a.exec();
}

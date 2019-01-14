#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);

    QFile file(":/style/qss");
    file.open(QFile::ReadOnly);

    QString style = QLatin1String(file.readAll());

    a.setStyleSheet(style);
    file.close();

    MainWindow w;
	w.show();

	return a.exec();
}

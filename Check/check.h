#ifndef CHECK_H
#define CHECK_H

#include <QHBoxLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QMenuBar>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QFileDialog>

#include "controller.h"

class Controller;

class Check : public QWidget {
	Q_OBJECT
private:
	Controller *controller;

	QListWidget *list;
	QLineEdit *tag;

public:
	Check(QWidget *parent = 0);
	~Check();

	QString getTag() const;
	QString selectedItem() const;

	void add() const;
	void remove() const;
	QString savePath();
};

#endif // WIDGET_H

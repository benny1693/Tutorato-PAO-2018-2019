#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "modello.h"

class Check;

class Controller : public QObject {
	Q_OBJECT

private:
	Modello* model;
	Check* view;

public:
	explicit Controller(Check*, QObject *parent = nullptr);
	~Controller();

public slots:
	void addItem() const;
	void removeItem() const;
	void save() const;
};

#endif // CONTROLLER_H

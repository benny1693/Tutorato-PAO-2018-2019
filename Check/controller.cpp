#include "controller.h"
#include "check.h"

Controller::Controller(Check *v, QObject *parent)
		: model(new Modello()), view(v), QObject(parent) {}

Controller::~Controller() {
	if (model)
		delete model;
}

// SLOT che indica al modello di aggiungere un elemento alla lista
void Controller::addItem() const {

	QString newElement = view->getTag();
	if (!newElement.trimmed().isEmpty()) {
		model->add(newElement.toStdString());
		view->add();
	}
}

// SLOT che indica al modello di togliere dalla lista un elemento
void Controller::removeItem() const {

	QString selectedElement = view->selectedItem();
	if (!selectedElement.isEmpty()){
		model->remove(selectedElement.toStdString());
		view->remove();
	}
}

// SLOT che indica al modello di salvare la lista nel file indicato da path
void Controller::save() const { model->save(view->savePath().toStdString()); }

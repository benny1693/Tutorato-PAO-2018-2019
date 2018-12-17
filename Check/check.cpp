#include "check.h"

Check::Check(QWidget *parent)
		: QWidget(parent), controller(new Controller(this)),
			list(new QListWidget()), tag(new QLineEdit()) {

	// Creo tutti i layout che mi servono
	QVBoxLayout *mainLayout = new QVBoxLayout();
	QHBoxLayout *secondLayout = new QHBoxLayout();
	QVBoxLayout *thirdLayout = new QVBoxLayout();
	QVBoxLayout *insLayout = new QVBoxLayout();
	QVBoxLayout *menuLayout = new QVBoxLayout();

	// Creo il menu
	QMenuBar *menuBar = new QMenuBar();
	QMenu *menu = new QMenu("File", menuBar);
	QAction *save = new QAction("Save", menu);
	QAction *exit = new QAction("Exit", menu);

	QPushButton *buttonAdd = new QPushButton("aggiungi");
	QPushButton *buttonRemove = new QPushButton("togli");

	// Assemblo il menu
	menuBar->addMenu(menu);
	menu->addAction(save);
	menu->addAction(exit);
	menuLayout->addWidget(menuBar);

	// Assemblo il mainLayout
	mainLayout->addLayout(menuLayout);
	mainLayout->addLayout(secondLayout);

	// Assemblo il secondLayout
	secondLayout->addWidget(list);
	secondLayout->addLayout(thirdLayout);

	// Assemblo il layout dell'inserimento
	insLayout->setSpacing(0);
	insLayout->addWidget(tag);
	insLayout->addWidget(buttonAdd);

	// Assemblo l'ultimo layout
	thirdLayout->addLayout(insLayout);
	thirdLayout->addWidget(buttonRemove);

	// Infine imposto il layout principale dell'applicazione
	setLayout(mainLayout);

	connect(exit, SIGNAL(triggered()), this, SLOT(close()));
	connect(buttonAdd, SIGNAL(clicked()), controller, SLOT(addItem()));
	connect(buttonRemove, SIGNAL(clicked()), controller, SLOT(removeItem()));
	connect(save, SIGNAL(triggered()), controller, SLOT(save()));
}

Check::~Check() {
	if (controller)
		delete controller;
}

// Restituisce il testo contenuto nell'etichetta
QString Check::getTag() const { return tag->text(); }

// Restituisce il nome dell'elemento selezionato
QString Check::selectedItem() const {
	if (!list->selectedItems().empty())
		return list->selectedItems().first()->text();
	else
		return "\0";
}

// Aggiunge alla lista un nuovo elemento
void Check::add() const {
	// Lo aggiungo
	list->addItem(tag->text());
	// Svuoto il campo di inserimento
	tag->clear();
}

// Toglie dalla lista l'elemento selezionato
void Check::remove() const {
	// Lo tolgo dalla lista
	qDeleteAll(list->selectedItems());
}

// Restituisce il path di salvataggio per il file
QString Check::savePath() {
	return QFileDialog::getSaveFileName(this, "Salva il File", "",
																			"File di Testo (*.txt)");
}

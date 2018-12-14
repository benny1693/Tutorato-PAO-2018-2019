#include "check.h"

Check::Check(QWidget *parent)
		: QWidget(parent), list(new QListWidget()), tag(new QLineEdit()) {

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
}

Check::~Check() {}

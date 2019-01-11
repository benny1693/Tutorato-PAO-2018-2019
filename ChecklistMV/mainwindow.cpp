#include "mainwindow.h"
#include "qlistmodeladapter.h"
#include "listview.h"
#include "qfilterproxymodel.h"

#include <QDesktopWidget>
#include <QApplication>

#include <QLayout>
#include <QPushButton>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent),
    proxymodel(new QFilterProxyModel(this)),
    model(new QListModelAdapter(this)),
    searchbar(new QLineEdit(this)),
    view(new ListView(this)) {

    // centra la finestra nello schermo
    move(QApplication::desktop()->screen()->rect().center() - rect().center());
    setWindowTitle(tr("Todo App")); // titolo applicazione
    setWindowIcon(QIcon("../ChecklistMV/data/icon.png")); // icona del programma

    // Widget a dimensione fissa
    setFixedSize(QSize(350, 700));

    // avvia caricamento del modello
    loadData();

    // fornisce alla view il modello dei dati che deve riflettere
    proxymodel->setSourceModel(model);
    view->setModel(proxymodel);

    searchbar->setPlaceholderText("Ricerca");

    // PULSANTI
    QPushButton* addButton = new QPushButton("Aggiungi", this);
    QPushButton* removeButton = new QPushButton("Rimuovi", this);
    QPushButton* saveButton = new QPushButton("Salva", this);
    QPushButton* toggleButton = new QPushButton("Speciale", this); // Special Todo toggle
    QPushButton* clearSearchButton = new QPushButton("X", this);

    // MENÙ e MENUBAR
    QMenuBar* menuBar = new QMenuBar();
    QMenu* menu = new QMenu("File", menuBar);
    QAction* saveAction = new QAction("Salva", menu);
    QAction* exitAction = new QAction("Esci", menu);
    // Setup del menù
    menuBar->addMenu(menu);
    menu->addAction(saveAction);
    menu->addAction(exitAction);

    // LAYOUT
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Searchbar sottolayout
    QHBoxLayout* searchLayout = new QHBoxLayout();
    searchLayout->addWidget(searchbar);
    searchLayout->addWidget(clearSearchButton);

    // Pulsanti sottolayout
    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(removeButton);
    buttonsLayout->addWidget(saveButton);
    buttonsLayout->addWidget(toggleButton);

    // Setup Main layout
    mainLayout->addWidget(menuBar);
    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(view, 0, Qt::AlignCenter);
    mainLayout->addLayout(buttonsLayout, 50); // stretch = 50 per distanziare i bottoni

    // CONNECT
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveData()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveData()));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(toggleButton, SIGNAL(clicked()), this, SLOT(toggleSpecialTodo()));
    connect(addButton, SIGNAL(clicked()), this, SLOT(addTodo()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeTodo()));
    connect(searchbar, SIGNAL(textChanged(QString)), this, SLOT(textFilterChanged()));
    connect(clearSearchButton, SIGNAL(clicked()), searchbar, SLOT(clear()));
}

// NB: non distrugge i QWidget (di quello se ne occupa Qt)
MainWindow::~MainWindow() {}

/*
 * Ritorna la dimensione ottimale della finestra
 */
QSize MainWindow::sizeHint() const {
    return QSize(300, 700);
}


void MainWindow::saveData() {
    try {
        model->saveToFile();
    } catch (std::exception) {
        QMessageBox box(QMessageBox::Warning, "Errore di salvataggio", "Non è stato possibile scrivere sul file", QMessageBox::Ok);
        box.exec();
    }
}

void MainWindow::loadData() {
    // in tale caso non serve passare per il proxymodel
    model->loadFromFile();
}

/* Aggiunge un nuovo Todo al modello e lo seleziona nella view */
void MainWindow::addTodo() {
    proxymodel->insertRows(proxymodel->rowCount(), 1);

    // Dà focus all'ultimo elemento aggiunto (lo seleziona)
    view->clearSelection();
    view->selectionModel()->clearCurrentIndex();
    view->selectionModel()->select(proxymodel->index(model->rowCount() - 1, 0), QItemSelectionModel::Select);
}

/* Rimuove il Todo selezionato nella view */
void MainWindow::removeTodo() {
    // prende l'elenco degli elementi selezionati dalla view
    const QModelIndexList selection = view->selectionModel()->selectedIndexes();
    if(selection.size() > 0)
        proxymodel->removeRows(selection.at(0).row(), 1);
}

/* Sostituisce il Todo selezionato (nella view) con un altro di tipo SpecialTodo/Todo */
void MainWindow::toggleSpecialTodo() {
    const QModelIndexList selection = view->selectionModel()->selectedIndexes();
    if(selection.size() > 0)
        proxymodel->toggleType(selection.at(0));
}

void MainWindow::textFilterChanged() {
    QRegExp regex(searchbar->text(), Qt::CaseInsensitive, QRegExp::Wildcard);
    proxymodel->setFilterRegExp(regex);
}


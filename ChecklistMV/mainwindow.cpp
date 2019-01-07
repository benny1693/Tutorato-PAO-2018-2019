#include "mainwindow.h"
#include "qlistmodeladapter.h"
#include "listview.h"

#include <QDesktopWidget>
#include <QApplication>

#include <QLayout>
#include <QPushButton>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent),
    model(new QListModelAdapter(this)),
    view(new ListView(this)) {

    // centra la finestra nello schermo
    move(QApplication::desktop()->screen()->rect().center() - rect().center());
    setWindowTitle(tr("Todo App")); // titolo applicazione
    setWindowIcon(QIcon("../ChecklistMV/data/icon.png")); // icona del programma

    // fornisce alla view il modello dei dati che deve riflettere
    view->setModel(model);

    // avvia caricamento del modello
    loadData();

    // PULSANTI
    QPushButton* addButton = new QPushButton("Aggiungi", this);
    QPushButton* removeButton = new QPushButton("Rimuovi", this);
    QPushButton* saveButton = new QPushButton("Salva", this);
    QPushButton* toggleButton = new QPushButton("Speciale", this); // Special Todo toggle

    // BARRA DEL MENÙ
    QMenuBar* menuBar = new QMenuBar();
    QMenu* menu = new QMenu("File", menuBar);
    QAction* saveAction = new QAction("Salva", menu);
    QAction* exitAction = new QAction("Esci", menu);
    // Assemblo menù
    menuBar->addMenu(menu);
    menu->addAction(saveAction);
    menu->addAction(exitAction);

    // LAYOUT
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(menuBar);
    mainLayout->addWidget(view, 0, Qt::AlignCenter);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(removeButton);
    buttonsLayout->addWidget(saveButton);
    buttonsLayout->addWidget(toggleButton);

    mainLayout->addLayout(buttonsLayout, 50); // stretch = 50 per distanziare un po' i bottoni

    // CONNECT
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveData()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveData()));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(toggleButton, SIGNAL(clicked()), this, SLOT(toggleSpecialTodo()));
    connect(addButton, SIGNAL(clicked()), this, SLOT(addTodo()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeTodo()));
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
        // .exec() diversamente da show blocca il flusso di esecuzione del programma finché l'utente non chiude il messaggio
    }
}

void MainWindow::loadData() {
    model->loadFromFile();
}

/* Aggiunge un nuovo Todo al modello e lo seleziona nella view */
void MainWindow::addTodo() {
    model->insertRows(model->rowCount());

    // Dà focus all'ultimo elemento aggiunto (lo seleziona)
    view->clearSelection();
    view->selectionModel()->clearCurrentIndex();
    view->selectionModel()->select(model->index(model->rowCount() - 1), QItemSelectionModel::Select);
}

/* Rimuove il Todo selezionato nella view */
void MainWindow::removeTodo() {
    // prende l'elenco degli elementi selezionati dalla view
    const QModelIndexList selection = view->selectionModel()->selectedIndexes();
    if(selection.size() > 0)
        model->removeRows(selection.at(0).row());
}

/* Sostituisce il Todo selezionato (nella view) con un altro di tipo SpecialTodo/Todo */
void MainWindow::toggleSpecialTodo() {
    const QModelIndexList selection = view->selectionModel()->selectedIndexes();
    if(selection.size() > 0)
        model->toggleType(selection.at(0));
}


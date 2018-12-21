#include "mainwindow.h"
#include "model.h"

// servono solo per centrare l'app nello schermo
#include <QDesktopWidget>
#include <QApplication>

#include <QLayout>
#include <QPushButton>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QListView>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent),
    model(new Model()),
    view(new QListView(this)) {

    // centra la finestra nello schermo
    move(QApplication::desktop()->screen()->rect().center() - rect().center());

    setWindowTitle(tr("Todo App")); // titolo applicazione
    setWindowIcon(QIcon("../ChecklistMV/data/icon.png")); // icona del programma

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
}

// NB: non distrugge i QWidget (di quello se ne occupa Qt)
MainWindow::~MainWindow() {
    delete model;
}


void MainWindow::saveData() {
    try {
        model->saveToFile("data");
    } catch (std::exception) {
        QMessageBox box(QMessageBox::Warning, "Errore di salvataggio", "Non è stato possibile scrivere sul file", QMessageBox::Ok);
        box.exec();
        // .exec() diversamente da show blocca il flusso di esecuzione del programma finché l'utente non chiude il messaggio
    }
}

void MainWindow::loadData() {
    model->loadFromFile("data");
}


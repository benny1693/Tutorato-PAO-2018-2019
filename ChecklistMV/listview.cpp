#include "listview.h"

#include <QMouseEvent>

ListView::ListView(QWidget* parent) : QListView(parent) {
    // rendiamo possibile la selezione di un singolo elemento alla volta
    setSelectionMode(QAbstractItemView::SingleSelection);
}

// override delle dimensioni della view per farla espandere con il pannello
QSize ListView::sizeHint() const {
    return QSize(350, 600);
}

/*
 * Ridefinisce il comportamento della vista al click del mouse su un elemento.
 * In particolare se si clicca al di sotto della lista di elementi pulisce la selezione.
 */
void ListView::mousePressEvent(QMouseEvent* event) {
     if (!indexAt(event->pos()).isValid()) {
        clearSelection();
        selectionModel()->clearCurrentIndex();
    }
    // altrimenti richiama il comportamento standard della QListView (che seleziona l'elemento cliccato)
    QListView::mousePressEvent(event);
}

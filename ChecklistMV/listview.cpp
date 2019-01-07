#include "listview.h"

ListView::ListView(QWidget* parent) : QListView(parent) {
    // rendiamo possibile la selezione di un singolo elemento alla volta
    setSelectionMode(QAbstractItemView::SingleSelection);
}

// override delle dimensioni della view per farla espandere con il pannello
QSize ListView::sizeHint() const {
    return QSize(350, 600);
}

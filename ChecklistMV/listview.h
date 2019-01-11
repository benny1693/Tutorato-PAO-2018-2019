#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <QListView>

/*
 * Classe utile per dimensionare correttamente la view con sizeHint()
 */
class ListView : public QListView {
public:
    ListView(QWidget* = nullptr);
    QSize sizeHint() const override;
    void mousePressEvent(QMouseEvent*) override;
};

#endif // LISTVIEW_H

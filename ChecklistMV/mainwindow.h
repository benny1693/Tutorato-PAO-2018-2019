#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class Model; // definizioni incomplete
class QListView;

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Model* model;
    QListView* view; // per ora è solo un placeholder, vedremo come si usa

    void loadData(); // non è chiamata da un pulsante quindi non serve sia uno SLOT

private slots:
    void saveData();
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class Model; // definizioni incomplete
class ListView;
class QListModelAdapter;

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

    QSize sizeHint() const override;

private:
    QListModelAdapter* model;
    ListView* view; // per ora è solo un placeholder, vedremo come si usa

    void loadData(); // non è chiamata da un pulsante quindi non serve sia uno SLOT

private slots:
    void saveData();
    void toggleSpecialTodo();
    void addTodo();
    void removeTodo();
};

#endif // MAINWINDOW_H

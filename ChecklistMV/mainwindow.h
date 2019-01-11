#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class Model; // definizioni incomplete
class ListView;
class QListModelAdapter;
class QLineEdit;
class QFilterProxyModel;

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

    QSize sizeHint() const override;

private:
    QFilterProxyModel* proxymodel;
    QListModelAdapter* model;
    QLineEdit* searchbar;
    ListView* view;

    void loadData(); // non è chiamata da un pulsante quindi non serve sia uno SLOT

private slots:
    void saveData();
    void toggleSpecialTodo();
    void addTodo();
    void removeTodo();
    void textFilterChanged();
};

#endif // MAINWINDOW_H

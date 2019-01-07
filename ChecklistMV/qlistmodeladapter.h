#ifndef QLISTMODELADAPTER_H
#define QLISTMODELADAPTER_H

#include <QAbstractListModel>

class Model;

/* Funziona da intermediario fra Model e la vista (ListView) */
class QListModelAdapter : public QAbstractListModel {
private:
    Model* model;

public:
    QListModelAdapter(QObject* = nullptr);
    ~QListModelAdapter() override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool insertRows(int, int = 1, const QModelIndex& = QModelIndex()) override;
    bool removeRows(int, int = 1, const QModelIndex& = QModelIndex()) override;
    bool toggleType(const QModelIndex&);

    void saveToFile() const;
    void loadFromFile();
};

#endif // QLISTMODELADAPTER_H

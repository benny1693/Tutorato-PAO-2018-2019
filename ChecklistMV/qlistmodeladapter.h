#ifndef QLISTMODELADAPTER_H
#define QLISTMODELADAPTER_H

#include <QAbstractListModel>

class Model;


class QListModelAdapter : public QAbstractListModel {
private:
    Model* model;

public:
    QListModelAdapter(QObject* = nullptr);
    ~QListModelAdapter() override;

    int rowCount(const QModelIndex& = QModelIndex()) const override;
    QVariant data(const QModelIndex&, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex&, const QVariant&, int);

    Qt::ItemFlags flags(const QModelIndex&) const override;

    bool insertRows(int, int = 1, const QModelIndex& = QModelIndex()) override;
    bool removeRows(int, int = 1, const QModelIndex& = QModelIndex()) override;
    bool toggleType(const QModelIndex&);

    void saveToFile() const;
    void loadFromFile();
};

#endif // QLISTMODELADAPTER_H

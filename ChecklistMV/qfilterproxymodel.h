#ifndef QFILTERPROXYMODEL_H
#define QFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

/*
 * Classe proxy che funzionerà da intermediario fra QListModelAdapter e ListView
 * per permettere alla vista di visualizzare solo certi elementi (Todo) sulla base
 * dell'input di ricerca inserito pur non dovendo effettuare alcuna operazione
 * sul reale modello dei dati sottostante e senza duplicare dati.
 */
class QFilterProxyModel : public QSortFilterProxyModel {
public:
    QFilterProxyModel(QObject* = nullptr);

    bool toggleType(const QModelIndex&);
    bool insertRows(int, int = 1, const QModelIndex& = QModelIndex()) override;

protected:
    bool filterAcceptsRow(int, const QModelIndex&) const override;
};

#endif // QFILTERPROXYMODEL_H

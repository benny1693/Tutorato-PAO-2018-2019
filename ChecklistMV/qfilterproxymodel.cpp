#include "qfilterproxymodel.h"
#include "qlistmodeladapter.h"

QFilterProxyModel::QFilterProxyModel(QObject* parent) : QSortFilterProxyModel (parent) {

}

bool QFilterProxyModel::toggleType(const QModelIndex& index) {
    QModelIndex index_source = mapToSource(index);
    return static_cast<QListModelAdapter*>(sourceModel())->toggleType(index_source);
}

bool QFilterProxyModel::insertRows(int begin, int count, const QModelIndex& parent) {
    bool result = sourceModel()->insertRows(begin, count, parent);
    invalidateFilter();
    return result;
}

bool QFilterProxyModel::filterAcceptsRow(int row_source, const QModelIndex&) const {
    // ritornare true se il testo del Todo matcha una RegExp
    // altrimenti ritorna false
    QModelIndex index_source = sourceModel()->index(row_source, 0);

    return sourceModel()->data(index_source).toString().contains(filterRegExp());
}

#include "qlistmodeladapter.h"
#include "model.h"
#include "todo.h"
#include "specialtodo.h"

#include <QFont>

QListModelAdapter::QListModelAdapter(QObject* parent) :
    QAbstractListModel(parent),
    model(new Model()) {}

QListModelAdapter::~QListModelAdapter() {
    delete model;
}

/*
 * Ritorna la dimensione (numero di righe) del modello
 */
int QListModelAdapter::rowCount(const QModelIndex &) const {
    return model->todoCount();
}

QVariant QListModelAdapter::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() >= model->todoCount())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        return QString::fromStdString(model->getTodo(index.row())->getText());
    }

    if (role == Qt::FontRole) {
        const string type = model->getTodo(index.row())->getType();
        if (type == "special") {
            QFont font("Arial", 14, QFont::Bold);
            font.setCapitalization(QFont::AllUppercase);
            return font;
        }
    }

    return QVariant();
}

bool QListModelAdapter::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (!index.isValid() && role != Qt::EditRole)
        return false;

    model->editTodo(index.row(), value.toString().toStdString());

    emit dataChanged(index, index);

    return true;
}

Qt::ItemFlags QListModelAdapter::flags(const QModelIndex& index) const {
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

/*
 * Inserisce 'count' nuove righe nel modello a partire dall'elemento di indice 'begin'
 */
bool QListModelAdapter::insertRows(int begin, int count, const QModelIndex& parent) {
    beginInsertRows(parent, begin, begin + count - 1);
    model->add(new Todo("Nuovo todo")); // effettuare l'aggiunta sul modello dei dati
    endInsertRows();
    return true;
}

/*
 * Rimuove 'count' righe dal modello dei dati a partire dall'indice 'begin'
 */
bool QListModelAdapter::removeRows(int begin, int count, const QModelIndex& parent) {
    beginRemoveRows(parent, begin, begin + count - 1);
    model->remove(begin);
    endRemoveRows();
    return true;
}

/*
 * Sostituisce un Todo in posizione 'index' con uno SpecialTodo e viceversa.
 * Il testo del Todo resta inalterato.
 */
bool QListModelAdapter::toggleType(const QModelIndex & index) {
    if (!index.isValid() || index.row() >= model->todoCount())
        return false;

    const Todo* todo = model->getTodo(index.row());
    const string type = todo->getType();
    const string text = todo->getText();
    Todo* newTodo = type == "special" ? new Todo(text) : new SpecialTodo(text);
    model->replace(index.row(), newTodo);

    // Avvisa la view che ha cambiato l'elemento in posizione 'index'
    emit dataChanged(index, index);

    return true;
}

/*
 * Salva il modello su file XML
 */
void QListModelAdapter::saveToFile() const {
    model->saveToFile();
}

/*
 * Carica il modello in memoria leggendo i Todo dal file XML
 */
void QListModelAdapter::loadFromFile() {
    model->loadFromFile();
}

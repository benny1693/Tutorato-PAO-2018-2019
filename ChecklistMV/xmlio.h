#ifndef XMLIO_H
#define XMLIO_H

#include <QString>

class Todo;

class XmlIO {
private:
    QString filename;
public:
    XmlIO(QString);
    QList<Todo*> read() const;
    void write(const QList<Todo*>&) const;
};

#endif // XMLIO_H

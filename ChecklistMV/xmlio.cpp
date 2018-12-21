#include "xmlio.h"
#include "todo.h"
#include "specialtodo.h"

#include <QFile>
#include <QSaveFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDebug>

XmlIO::XmlIO(QString filepath) : filename(filepath) {}

QList<Todo*> XmlIO::read() const {
    // Crea una lista
    QList<Todo*> list;

    // Apre un file (QFile)
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Non è stato possibile aprire il file" << file.errorString();
        return  list;
    }

    // Lettura da file XML
    QXmlStreamReader reader(&file); // QIODevice*
    if(reader.readNextStartElement()) {
        if(reader.name() == "root") {
            while(reader.readNextStartElement()) {
                if(reader.name() == "todo") {
                    // legge l'attributo 'type'
                    const QXmlStreamAttributes attributes = reader.attributes();
                    const QString type = attributes.hasAttribute("type") ? attributes.value("type").toString() : "";

                    // legge il testo del Todo contenuto nei tag
                    const QString textValue = reader.readElementText();

                    // creiamo un nuovo todo con il tipo giusto e lo aggiunge alla lista
                    if(type == "standard")
                        list.append(new Todo(textValue.toStdString()));
                    else if(type == "special")
                        list.append(new SpecialTodo(textValue.toStdString()));
                    qDebug() << "Letto Todo " + type + ": " + textValue;
                }
                else
                    reader.skipCurrentElement();
            }
        }
    }

    // Chiude il file e ritorna la lista con i Todo letti
    file.close();
    return list;
}

void XmlIO::write(const QList<Todo*>& list) const {
    /* QSaveFile rispetto a QFile è più adatto per effettuare scritture su disco. Gestisce meglio
       i casi di errore, garantendo che non vengano persi i dati del file in caso di errori in scrittura */
    QSaveFile file(filename);

    // Apre un file. Se non si apre lancia una eccezione.
    if(!file.open(QIODevice::WriteOnly)) {
        throw std::exception();
        // NB: la cosa giusta da fare sarebbe creare un tipo eccezione. std::exception è troppo generica.
    }

    QXmlStreamWriter writer(&file);

    writer.setAutoFormatting(true); // Per leggibilità del file XML
    writer.writeStartDocument();    // Scrive le intestazioni XML
    writer.writeComment("File di salvataggio dell'applicazione. Non modificare a mano.");

    writer.writeStartElement("root");                                // <root>

    QListIterator<Todo*> it(list); // Java style iterator

    while(it.hasNext()) {
        writer.writeStartElement("todo");                            // <todo>

        // Legge il testo ed il tipo del todo
        const Todo* todo = it.next();
        const std::string type = todo->getType();
        const std::string text = todo->getText();

        writer.writeAttribute("type", QString::fromStdString(type)); // <todo type="valore">
        writer.writeCharacters(QString::fromStdString(text));        // <todo type="valore">testo
        writer.writeEndElement();                                    // </todo>
        if (writer.hasError()) // se c'è stato un problema in scrittura interrompe ed esce
            throw std::exception();
    }

    writer.writeEndElement();                                        // </root>
    writer.writeEndDocument();  // chiude eventuali tag lasciati aperti e aggiunge una riga vuota alla fine

    file.commit(); // Scrive il file temporaneo su disco
}

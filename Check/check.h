#ifndef CHECK_H
#define CHECK_H

#include <QWidget>
#include<QListWidget>
#include<QLineEdit>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QMenuBar>
#include<QPushButton>


class Check : public QWidget {
	Q_OBJECT
private:
	QListWidget* list;
	QLineEdit* tag;

public:
	Check(QWidget *parent = 0);
	~Check();
};

#endif // WIDGET_H

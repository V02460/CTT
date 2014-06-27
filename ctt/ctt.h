#ifndef CTT_H
#define CTT_H

#include <QtWidgets/QMainWindow>
#include "ui_ctt.h"

class ctt : public QMainWindow
{
	Q_OBJECT

public:
	ctt(QWidget *parent = 0);
	~ctt();

private:
	Ui::cttClass ui;
};

#endif // CTT_H

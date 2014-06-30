#ifndef CTT_H
#define CTT_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QtWidgets/QMainWindow>
#include "ui_ctt.h"

class ctt : public QMainWindow
{
	Q_OBJECT

public:
	typedef QScopedPointer<ctt> uptr;
	typedef QSharedPointer<ctt> sptr;
	typedef QWeakPointer<ctt> wptr;

	ctt(QWidget *parent = 0);
	~ctt();

private:
	Ui::cttClass ui;
};

#endif // CTT_H

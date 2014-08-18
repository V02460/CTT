#ifndef CTT_H
#define CTT_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QtWidgets/QMainWindow>

#include <QLabel>
#include "ui_ctt.h"

class ctt : public QMainWindow {
    Q_OBJECT
public:
    typedef QScopedPointer<ctt> uptr;
    typedef QSharedPointer<ctt> sptr;
    typedef QWeakPointer<ctt> wptr;

    ctt(QWidget *parent = 0);
    ~ctt();

    QLabel *getLabel() {
        return this->ui.label;
    }

private:
    Ui::cttClass ui;
};

#endif // CTT_H

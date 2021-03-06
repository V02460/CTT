#ifndef _TIMESHIFTFILTERTEST_H
#define _TIMESHIFTFILTERTEST_H

#include <QtTest/QtTest>
#include <QObject>
#include "YUVDataVideo.h"

class TimeshiftFilterTest : public QObject {
    Q_OBJECT

public:
    TimeshiftFilterTest();

    private slots:
    void initTestCase();
    void testRun();
    void wrongParams();
    void memento();

private:
    QSharedPointer<QOpenGLContext> testContext;
    ::model::video::YUVDataVideo::sptr video;
};

#endif  //_TIMESHIFTFILTERTEST_H
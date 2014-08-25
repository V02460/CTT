#ifndef _TIMESHIFTFILTERTEST_H
#define _TIMESHIFTFILTERTEST_H

#include <QtTest/QtTest>
#include <QObject>
#include <QOffscreenSurface>
#include "YUVDataVideo.h"

class TimeshiftFilterTest : public QObject {
    Q_OBJECT

public:
    TimeshiftFilterTest();

    private slots:
    void initTestCase();
    void testRun();
    void wrongParams();

private:
    QSharedPointer<QOpenGLContext> testContext;
    QOffscreenSurface surface;
    ::model::video::YUVDataVideo::sptr video;
};

#endif  //_TIMESHIFTFILTERTEST_H
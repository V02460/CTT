#ifndef _RESCALEFILTERTEST_H
#define _RESCALEFILTERTEST_H

#include <QtTest/QtTest>
#include <QObject>
#include "YUVDataVideo.h"

class RescaleFilterTest : public QObject {
    Q_OBJECT

public:
    RescaleFilterTest();

    private slots:
    void initTestCase();
    void testRun();
    void wrongParams();
    void memento();

private:
    QSharedPointer<QOpenGLContext> testContext;
    ::model::video::YUVDataVideo::sptr video;
};

#endif  //_RESCALEFILTERTEST_H
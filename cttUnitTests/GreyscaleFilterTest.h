#ifndef _GREYSCALEFILTERTEST_H
#define _GREYSCALEFILTERTEST_H

#include <QtTest/QtTest>
#include <QObject>
#include <QOffscreenSurface>
#include "YUVDataVideo.h"

class GreyscaleFilterTest : public QObject {
    Q_OBJECT

public:
    GreyscaleFilterTest();

    private slots:
    void initTestCase();
    void testRun();
    void wrongParams();

private:
    QSharedPointer<QOpenGLContext> testContext;
    QOffscreenSurface surface;
    ::model::video::YUVDataVideo::sptr video;
};

#endif  //_GREYSCALEFILTERTEST_H
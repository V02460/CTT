#ifndef _MIXFILTERTEST_H
#define _MIXFILTERTEST_H

#include <QtTest/QtTest>
#include <QObject>
#include <QOffscreenSurface>
#include "YUVDataVideo.h"

class MixFilterTest : public QObject {
    Q_OBJECT

public:
    MixFilterTest();

    private slots:
    void initTestCase();
    void testRun();
    void wrongParams();
    void differentSize();

private:
    QSharedPointer<QOpenGLContext> testContext;
    QOffscreenSurface surface;
    ::model::video::YUVDataVideo::sptr video1;
    ::model::video::YUVDataVideo::sptr video2;
};

#endif
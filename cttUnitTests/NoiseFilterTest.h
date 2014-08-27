#ifndef _NOISEFILTERTEST_H
#define _NOISEFILTERTEST_H

#include <QtTest/QtTest>
#include <QObject>
#include <QOffscreenSurface>
#include "YUVDataVideo.h"

class NoiseFilterTest : public QObject {
    Q_OBJECT

public:
    NoiseFilterTest();

    private slots:
    void initTestCase();
    void testRun();
    void wrongParams();

private:
    QSharedPointer<QOpenGLContext> testContext;
    QOffscreenSurface surface;
    ::model::video::YUVDataVideo::sptr video;
};

#endif  //_NOISEFILTERTEST_H
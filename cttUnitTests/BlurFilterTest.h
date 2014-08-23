#ifndef _BLURFILTERTEST_H
#define _BLURFILTERTEST_H

#include <QtTest/QtTest>
#include <QObject>
#include <QOffscreenSurface>
#include "YUVDataVideo.h"

class BlurFilterTest : public QObject {
    Q_OBJECT

public:
    BlurFilterTest();

private slots:
    void initTestCase();
    void testRun();
    void wrongParams();

private:
    QSharedPointer<QOpenGLContext> testContext;
    QOffscreenSurface surface;
    ::model::video::YUVDataVideo::sptr video;
};

#endif
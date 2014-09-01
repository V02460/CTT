#ifndef _INVERTFILTERTEST_H
#define _INVERTFILTERTEST_H

#include <QtTest/QtTest>
#include <QObject>
#include <QOffscreenSurface>
#include "YUVDataVideo.h"

class InvertFilterTest : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void testRun();
    void wrongParams();

private:
    QSharedPointer<QOpenGLContext> testContext;
    QOffscreenSurface surface;
    ::model::video::YUVDataVideo::sptr video;
};

#endif  //_INVERTFILTERTEST_H
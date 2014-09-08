#ifndef _BLURFILTERTEST_H
#define _BLURFILTERTEST_H

#include <QtTest/QtTest>
#include <QObject>
#include "YUVDataVideo.h"

class BlurFilterTest : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void testRun();
    void wrongParams();
    void memento();

private:
    QSharedPointer<QOpenGLContext> testContext;
    ::model::video::YUVDataVideo::sptr video;
};

#endif
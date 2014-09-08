#ifndef _INVERTFILTERTEST_H
#define _INVERTFILTERTEST_H

#include <QtTest/QtTest>
#include <QObject>
#include "YUVDataVideo.h"

class InvertFilterTest : public QObject {
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

#endif  //_INVERTFILTERTEST_H
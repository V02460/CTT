#ifndef _HEATMAPOVERLAYTEST_H
#define _HEATMAPOVERLAYTEST_H

#include <QtTest/QtTest>
#include <QObject>
#include "Module.h"
#include "YUVDataVideo.h"

class HeatmapOverlayTest : public QObject {
    Q_OBJECT

public:
    HeatmapOverlayTest();

    private slots:
    void initTestCase();
    void testRun();
    //void wrongParams();

private:
    QSharedPointer<QOpenGLContext> testContext;
    ::model::Module::sptr video1;
    ::model::Module::sptr video2;
};

#endif  //_HEATMAPOVERLAYTEST_H
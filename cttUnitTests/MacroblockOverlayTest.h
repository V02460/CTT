#ifndef _MACROBLOCKOVERLAYTEST_H
#define _MACROBLOCKOVERLAYTEST_H

#include <QtTest/QtTest>
#include <QObject>
#include <QOffscreenSurface>
#include "YUVDataVideo.h"

class MacroblockOverlayTest : public QObject {
    Q_OBJECT

public:
    MacroblockOverlayTest();

    private slots:
    void initTestCase();
    // TODO: create a succeeding test
    //void testRun();
    void noMetadata();
    //void wrongParams();

private:
    QSharedPointer<QOpenGLContext> testContext;
    QOffscreenSurface surface;
    ::model::video::YUVDataVideo::sptr video;
};

#endif  //_MACROBLOCKOVERLAYTEST_H
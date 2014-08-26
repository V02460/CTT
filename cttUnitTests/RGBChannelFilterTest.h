#ifndef _RGBCHANNELFILTERTEST_H
#define _RGBCHANNELFILTERTEST_H

#include <QtTest/QtTest>
#include <QObject>
#include <QOffscreenSurface>
#include "YUVDataVideo.h"

class RGBChannelFilterTest : public QObject {
    Q_OBJECT

public:
    RGBChannelFilterTest();

    private slots:
    void initTestCase();
    void testRun();
    void wrongParams();

private:
    QSharedPointer<QOpenGLContext> testContext;
    QOffscreenSurface surface;
    ::model::video::YUVDataVideo::sptr video;
};

#endif  //_RGBCHANNELFILTERTEST_H
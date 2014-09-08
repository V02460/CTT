#ifndef _RGBCHANNELFILTERTEST_H
#define _RGBCHANNELFILTERTEST_H

#include <QtTest/QtTest>
#include <QObject>
#include "YUVDataVideo.h"

class RGBChannelFilterTest : public QObject {
    Q_OBJECT

public:
    RGBChannelFilterTest();

    private slots:
    void initTestCase();
    void testRun();
    void wrongParams();
    void memento();

private:
    QSharedPointer<QOpenGLContext> testContext;
    ::model::video::YUVDataVideo::sptr video;
};

#endif  //_RGBCHANNELFILTERTEST_H
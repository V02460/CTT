#ifndef _MACROBLOCKOVERLAYTEST_H
#define _MACROBLOCKOVERLAYTEST_H

#include <QtTest/QtTest>
#include <QObject>
#include "YUVDataVideo.h"

class MacroblockOverlayTest : public QObject {
    Q_OBJECT

public:
    MacroblockOverlayTest();

    private slots:
    void initTestCase();
    void testRun();
    void noMetadata();
    //void wrongParams();

private:
    QSharedPointer<QOpenGLContext> testContext;
    ::model::video::YUVDataVideo::sptr video;
    ::model::video::YUVDataVideo::sptr noMetadataVideo;
};

#endif  //_MACROBLOCKOVERLAYTEST_H
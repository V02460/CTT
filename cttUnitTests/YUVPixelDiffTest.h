#ifndef _YUVPIXELDIFFTEST_H
#define _YUVPIXELDIFFTEST_H

#include <QtTest/QtTest>

#include <QObject>

#include "YUVDataVideo.h"

namespace model {
namespace difference {

class YUVPixelDiffTest : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void testRun();
    void badArgs();

private:
    QSharedPointer<QOpenGLContext> testContext;
    ::model::video::YUVDataVideo::sptr video1;
    ::model::video::YUVDataVideo::sptr video2;
};

}  // namespace difference
}  // namespace model

#endif _YUVPIXELDIFFTEST_H
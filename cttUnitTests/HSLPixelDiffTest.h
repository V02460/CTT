#ifndef _HSLPIXELDIFFTEST_H
#define _HSLPIXELDIFFTEST_H

#include <QtTest/QtTest>

#include <QObject>
#include <QOpenGLContext>
#include <QOffscreenSurface>

#include "YUVDataVideo.h"

namespace model {
namespace difference {

class HSLPixelDiffTest : public QObject {
    Q_OBJECT

        private slots:
    void initTestCase();
    void testRun();
    void badArgs();

private:
    QSharedPointer<QOpenGLContext> testContext;
    QOffscreenSurface surface;
    ::model::video::YUVDataVideo::sptr video1;
    ::model::video::YUVDataVideo::sptr video2;
};

}  // namespace difference
}  // namespace model

#endif _HSLPIXELDIFFTEST_H
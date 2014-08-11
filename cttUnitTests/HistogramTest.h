#ifndef _HISTOGRAMTEST_H
#define _HISTOGRAMTEST_H

#include <QtTest/QtTest>
#include <QObject>
#include <QOffscreenSurface>
#include <QSharedPointer>
#include <QOpenGLContext>
#include <QImage>

#include "../ctt/RedHistogram.h"
#include "../ctt/GreenHistogram.h"
#include "../ctt/BlueHistogram.h"
#include "../ctt/HueHistogram.h"
#include "../ctt/SaturationHistogram.h"
#include "../ctt/LuminanceHistogram.h"

namespace model {
namespace frame {
namespace histogram {

class HistogramTest : public QObject {
    Q_OBJECT

private slots:
//     void initTestCase();
//     void histogramTypes();
    // TODO: test get value

private:
    QSharedPointer<QOpenGLContext> testContext;
    QOffscreenSurface surface;
    QImage testImage;

    RedHistogram *redHistogram;
    GreenHistogram *greenHistogram;
    BlueHistogram *blueHistogram;
    HueHistogram *hueHistogram;
    SaturationHistogram *saturationHistogram;
    LuminanceHistogram *luminanceHistogram;
};

}  // namespace histogram
}  // namespace frame
}  // namespace model

#endif
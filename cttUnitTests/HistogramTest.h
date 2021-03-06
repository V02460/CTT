#ifndef _HISTOGRAMTEST_H
#define _HISTOGRAMTEST_H

#include <QtTest/QtTest>
#include <QObject>
#include <QSharedPointer>
#include <QOpenGLContext>
#include <QImage>

#include "RedHistogram.h"
#include "GreenHistogram.h"
#include "BlueHistogram.h"
#include "HueHistogram.h"
#include "SaturationHistogram.h"
#include "LuminanceHistogram.h"

namespace model {
namespace frame {
namespace histogram {

class HistogramTest : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void histogramTypes();
    void getValues();

private:
    QSharedPointer<QOpenGLContext> testContext;
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
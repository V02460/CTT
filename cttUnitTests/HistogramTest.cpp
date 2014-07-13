#include "HistogramTest.h"

#include "Frame.h"

namespace model {
namespace frame {
namespace histogram {

void HistogramTest::initTestCase() {
    surface.create();
    testContext = QSharedPointer<QOpenGLContext>(new QOpenGLContext());
    testContext->create();
    QVERIFY2(testContext->makeCurrent(&surface), "Couldn't initialize OGL Context.");

    testImage.load(":/cttUnitTests/BigBuckBunny.png");

    if (testImage.isNull()) {
        QFAIL("Unable to load image.");
    }

    Frame frame(testContext, testImage);

    redHistogram = new RedHistogram(frame);
    greenHistogram = new GreenHistogram(frame);
    blueHistogram = new BlueHistogram(frame);
    hueHistogram = new HueHistogram(frame);
    saturationHistogram = new SaturationHistogram(frame);
    luminanceHistogram = new LuminanceHistogram(frame);
}

void HistogramTest::histogramTypes() {
    QVERIFY2(redHistogram->getType() == Histogram::Red, "Red histogram does not return correct type.");
    QVERIFY2(greenHistogram->getType() == Histogram::Green, "Green histogram does not return correct type.");
    QVERIFY2(blueHistogram->getType() == Histogram::Blue, "Blue histogram does not return correct type.");
    QVERIFY2(hueHistogram->getType() == Histogram::Hue, "Hue histogram does not return correct type.");
    QVERIFY2(saturationHistogram->getType() == Histogram::Saturation, "Saturation histogram does not return correct type.");
    QVERIFY2(luminanceHistogram->getType() == Histogram::Luminance, "Luminance histogram does not return correct type.");
}

}  // namespace histogram
}  // namespace frame
}  // namespace model
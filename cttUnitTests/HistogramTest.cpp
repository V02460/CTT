#include "HistogramTest.h"

#include "Frame.h"
#include "GlobalContext.h"

#include "IllegalArgumentException.h"

namespace model {
namespace frame {
namespace histogram {

using ::model::GlobalContext;
using ::exception::IllegalArgumentException;

void HistogramTest::initTestCase() {
    testContext = GlobalContext::get();

    testImage.load(":/cttUnitTests/BigBuckBunny.png");

    if (testImage.isNull()) {
        QFAIL("Unable to load image.");
    }

    Frame::sptr frame(new Frame(testContext, testImage));

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

void HistogramTest::getValues() {
    redHistogram->getValue(0);
    greenHistogram->getValue(128);
    QVERIFY_EXCEPTION_THROWN(blueHistogram->getValue(512), IllegalArgumentException);
    QVERIFY_EXCEPTION_THROWN(hueHistogram->getValue(666), IllegalArgumentException);
    QVERIFY_EXCEPTION_THROWN(luminanceHistogram->getValue(256), IllegalArgumentException);
    saturationHistogram->getValue(255);
}

}  // namespace histogram
}  // namespace frame
}  // namespace model
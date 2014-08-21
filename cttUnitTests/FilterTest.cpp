#include "FilterTest.h"

#include "../ctt/Frame.h"

namespace model {
namespace filter {

using ::model::frame::Frame;

void FilterTest::initTestCase() {
    surface.create();
    testContext = QSharedPointer<QOpenGLContext>(new QOpenGLContext());
    testContext->create();
    QVERIFY2(testContext->makeCurrent(&surface), "Couldn't initialize OGL Context.");

    testImage.load(":/cttUnitTests/BigBuckBunny.png");

    if (testImage.isNull()) {
        QFAIL("Unable to load image.");
    }

    Frame frame(testContext, testImage);
}

void FilterTest::dummyCase() {

}

}  // namespace filter
}  // namespace model
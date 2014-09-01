#include "FilterTest.h"

#include "Frame.h"
#include "GlobalContext.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::model::GlobalContext;

void FilterTest::initTestCase() {
    testContext = GlobalContext::get();

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
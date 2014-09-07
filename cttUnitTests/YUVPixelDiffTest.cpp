#include "YUVPixelDiffTest.h"

#include "YUVPixelDiff.h"
#include "GlobalContext.h"

#include "IllegalArgumentException.h"

namespace model {
namespace difference {

using ::model::video::YUVDataVideo;
using ::exception::IllegalArgumentException;
using ::model::GlobalContext;
using ::model::video::YUVType;


void YUVPixelDiffTest::initTestCase() {
    testContext = GlobalContext::get();

    video1.reset(new YUVDataVideo("Resources/Videos/YUV422/squirrel-720x576-422P.yuv",
        QSize(720, 576),
        24,
        YUVType::YUV422,
        testContext));

    video2.reset(new YUVDataVideo("Resources/Videos/YUV444/squirrel-720x576-444P.yuv",
        QSize(720, 576),
        24,
        YUVType::YUV444,
        testContext));
}

void YUVPixelDiffTest::testRun() {
    YUVPixelDiff diff(video1, video2);
    diff.getDiff(5);
    diff.getPixelDiff(8);
}

void YUVPixelDiffTest::badArgs() {
    YUVPixelDiff diff(video1, video2);
    QVERIFY_EXCEPTION_THROWN(diff.getDiff(-6), IllegalArgumentException);
    QVERIFY_EXCEPTION_THROWN(diff.getPixelDiff(666), IllegalArgumentException);
}

}  // namespace difference
}  // namespace model

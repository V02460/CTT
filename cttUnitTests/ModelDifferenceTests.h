#ifndef _MODELDIFFERENCETESTS_H
#define _MODELDIFFERENCETESTS_H

#include "TestResult.h"

#include "ModelFrameHistogramTests.h"

#include "HSLPixelDiffTest.h"
#include "YUVPixelDiffTest.h"

namespace model {
namespace difference {

static TestResult test(int argc, char *argv[]) {
    TestResult r("difference");

    HSLPixelDiffTest hslPixelDiff;
    YUVPixelDiffTest yuvPixelDiff;
    r << TestResult("HSLPixelDiffTest", QTest::qExec(&hslPixelDiff, argc, argv))
      << TestResult("YUVPixelDiffTest", QTest::qExec(&yuvPixelDiff, argc, argv));

    return r;
}

}  // namespace difference
}  // namespace model

#endif  //_MODELDIFFERENCETESTS_H
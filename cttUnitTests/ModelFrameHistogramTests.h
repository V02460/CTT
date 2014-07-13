#ifndef _MODELFRAMEHISTOGRAMTESTS_H
#define _MODELFRAMEHISTOGRAMTESTS_H

#include "TestResult.h"

#include "HistogramTest.h"

namespace model {
namespace frame {
namespace histogram {

static TestResult test(int argc, char *argv[]) {
    TestResult r("histogram");

    HistogramTest histogramTest;
    r << TestResult("HistogramTest", QTest::qExec(&histogramTest, argc, argv));

    return r;
}

}  // namespace histogram
}  // namespace frame
}  // namespace model

#endif  //_MODELFRAMEHISTOGRAMTESTS_H
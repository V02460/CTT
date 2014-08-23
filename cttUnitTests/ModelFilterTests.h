#ifndef _MODELFILTERTESTS_H
#define _MODELFILTERTESTS_H

#include "TestResult.h"

#include "FilterTest.h"
#include "BlurFilterTest.h"
#include "MixFilterTest.h"

namespace model {
namespace filter {

static TestResult test(int argc, char *argv[]) {
    TestResult r("filter");

    FilterTest filterTest;
    BlurFilterTest blurFilterTest;
    MixFilterTest mixFilterTest;
    r << TestResult("FilterTest", QTest::qExec(&filterTest, argc, argv))
      << TestResult("BlurFilterTest", QTest::qExec(&blurFilterTest, argc, argv))
      << TestResult("MixFilterTest", QTest::qExec(&mixFilterTest, argc, argv));

    return r;
}

}  // namespace filter
}  // namespace model

#endif
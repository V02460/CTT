#ifndef _MODELFILTERTESTS_H
#define _MODELFILTERTESTS_H

#include "TestResult.h"

#include "FilterTest.h"
#include "BlurFilterTest.h"
#include "MixFilterTest.h"
#include "RescaleFilterTest.h"

#include "FilteredVideoTest.h"

namespace model {
namespace filter {

static TestResult test(int argc, char *argv[]) {
    TestResult r("filter");

    FilterTest filterTest;
    BlurFilterTest blurFilterTest;
    MixFilterTest mixFilterTest;
    RescaleFilterTest rescaleFilterTest;

    FilteredVideoTest filteredVideoTest;

    r << TestResult("FilterTest", QTest::qExec(&filterTest, argc, argv))
      << TestResult("BlurFilterTest", QTest::qExec(&blurFilterTest, argc, argv))
      << TestResult("MixFilterTest", QTest::qExec(&mixFilterTest, argc, argv))
      << TestResult("RescaleFilterTest", QTest::qExec(&rescaleFilterTest, argc, argv))

      << TestResult("FilteredVideoTest", QTest::qExec(&filteredVideoTest, argc, argv));

    return r;
}

}  // namespace filter
}  // namespace model

#endif
#ifndef _MODELFILTERTESTS_H
#define _MODELFILTERTESTS_H

#include "TestResult.h"

#include "FilterTest.h"

namespace model {
namespace filter {

static TestResult test(int argc, char *argv[]) {
    TestResult r("filter");

    FrameTest filterTest;
    r << TestResult("FilterTest", QTest::qExec(&filterTest, argc, argv));

    return r;
}

}  // namespace filter
}  // namespace model

#endif
#ifndef _MODELFRAMETESTS_H
#define _MODELFRAMETESTS_H

#include "TestResult.h"

#include "FrameTest.h"

namespace model {
namespace frame {

static TestResult test(int argc, char *argv[]) {
    TestResult r("frame");

    FrameTest frameTest;
    r << TestResult("FrameTest", QTest::qExec(&frameTest, argc, argv));

    return r;
}

}
}

#endif
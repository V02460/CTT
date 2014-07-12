#ifndef _MODELPLAYERTESTS_H
#define _MODELPLAYERTESTS_H

#include "TestResult.h"

#include "VideoScrubberTest.h"

namespace model {
namespace player {

static TestResult test(int argc, char *argv[]) {
    TestResult r("player");

    VideoScrubberTest videoScrubberTest;
    r << TestResult("VideoScrubberTest", QTest::qExec(&videoScrubberTest, argc, argv));

    return r;
}

}
}

#endif
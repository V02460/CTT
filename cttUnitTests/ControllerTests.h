#ifndef _CONTROLLERTESTS_H
#define _CONTROLLERTESTS_H

#include "TestResult.h"

#include "VideoListControllerTest.h"

//#include "ModelFilterTests.h"

namespace controller {

static TestResult test(int argc, char *argv[]) {
    TestResult r("controller");

	VideoListControllerTest videoListControllerTest;

	r << TestResult("VideoListControllerTest", QTest::qExec(&videoListControllerTest, argc, argv));

    //r << filter::test(argc, argv);

    return r;
}

}  // namespace controller

#endif  //_CONTROLLERTESTS_H
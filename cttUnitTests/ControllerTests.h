#ifndef _CONTROLLERTESTS_H
#define _CONTROLLERTESTS_H

#include "TestResult.h"

#include "VideoListControllerTest.h"
#include "ExtendedVideoListControllerTest.h"

//#include "ModelFilterTests.h"

namespace controller {

static TestResult test(int argc, char *argv[]) {
    TestResult r("controller");

	VideoListControllerTest videoListControllerTest;
	ExtendedVideoListControllerTest extendedVideoListControllerTest;

	r << TestResult("VideoListControllerTest", QTest::qExec(&videoListControllerTest, argc, argv))
      << TestResult("ExtendedVideoListControllerTest", QTest::qExec(&extendedVideoListControllerTest, argc, argv));
    //r << filter::test(argc, argv);

    return r;
}

}  // namespace controller

#endif  //_CONTROLLERTESTS_H
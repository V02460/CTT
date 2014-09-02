#include "VideoListControllerTest.h"

#include "GlobalContext.h"

using model::GlobalContext;

void VideoListControllerTest::initTestCase() {
    testContext = GlobalContext::get();
}

void VideoListControllerTest::testRun() {
    QFAIL("VideoListControllerTest.cpp was missing from the commit");
}
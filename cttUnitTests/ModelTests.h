#ifndef _MODELTESTS_H
#define _MODELTESTS_H

#include "TestResult.h"

#include "ModelFilterTests.h"
#include "ModelFrameTests.h"
#include "ModelDifferenceTests.h"
#include "ModelSaveableTests.h"
#include "ModelPlayerTests.h"
#include "ModelVideoTests.h"
#include "ABXTesttest.h"

namespace model {

static TestResult test(int argc, char *argv[]) {
    TestResult r("model");

	ABXTesttest aBXTesttest;
    r << filter::test(argc, argv) 
      << frame::test(argc, argv)
      << difference::test(argc, argv)
      << saveable::test(argc, argv)
      << player::test(argc, argv)
      << video::test(argc, argv)
	  << TestResult("ABXTestTest", QTest::qExec(&aBXTesttest, argc, argv));

    return r;
}

}  // namespace model

#endif
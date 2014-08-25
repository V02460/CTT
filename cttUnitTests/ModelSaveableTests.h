#ifndef _MODELSAVEABLESTESTS_H
#define _MODELSAVEABLETESTS_H

#include "TestResult.h"

#include "MementoTest.h"
#include "SaveableListTest.h"

namespace model {
namespace saveable {

static TestResult test(int argc, char *argv[]) {
    TestResult r("saveable");

    MementoTest mementoTest;
	SaveableListTest saveableListTest;
	r << TestResult("MementoTest", QTest::qExec(&mementoTest, argc, argv))
      << TestResult("SaveableListTest", QTest::qExec(&saveableListTest, argc, argv));

    return r;
}

}
}

#endif
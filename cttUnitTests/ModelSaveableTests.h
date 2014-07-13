#ifndef _MODELSAVEABLESTESTS_H
#define _MODELSAVEABLETESTS_H

#include "TestResult.h"

#include "MementoTest.h"

namespace model {
namespace saveable {

static TestResult test(int argc, char *argv[]) {
    TestResult r("memento");

    MementoTest frameTest;
    r << TestResult("MementoTest", QTest::qExec(&frameTest, argc, argv));

    return r;
}

}
}

#endif
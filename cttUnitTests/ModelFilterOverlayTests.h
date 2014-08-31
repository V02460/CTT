#ifndef _MODELFILTEROVERLAYTESTS_H
#define _MODELFILTEROVERLAYTESTS_H

#include "TestResult.h"

#include "MacroblockOverlayTest.h"

namespace model {
namespace filter {
namespace overlay {

static TestResult test(int argc, char *argv[]) {
    TestResult r("overlay");

    MacroblockOverlayTest macroblockOverlayTest;

    r << TestResult("MacroblockOverlayTest", QTest::qExec(&macroblockOverlayTest, argc, argv));

    return r;
}

}  // namespace overlay
}  // namespace filter
}  // namespace model

#endif  //_MODELFILTEROVERLAYTESTS_H
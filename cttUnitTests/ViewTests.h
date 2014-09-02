#ifndef _VIEWTESTS_H
#define _VIEWTESTS_H

#include "TestResult.h"

namespace view {

static TestResult test(int argc, char *argv[]) {
	TestResult r("view");

    // TODO:
    // r << qTest();

	return r;
}

} //namespace view

#endif 
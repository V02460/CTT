#ifndef _VIEWTESTS_H
#define _VIEWTESTS_H

#include "VideoWidgetTest.h"
#include "ListedPushButtonTest.h"
#include "Frame.h"
#include <QApplication>

namespace view {
static TestResult test(int argc, char *argv[], QApplication *a) {
	TestResult r("view");

	/*VideoWidgetTest videoWidgetTest = VideoWidgetTest();
	videoWidgetTest.show();*/

	ListedPushButtonTest listedPushButtonTest = ListedPushButtonTest();
	listedPushButtonTest.show();
	a->exec();

	return r;
}
} //namespace view

#endif 
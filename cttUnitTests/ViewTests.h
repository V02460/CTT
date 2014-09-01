#ifndef _VIEWTESTS_H
#define _VIEWTESTS_H

#include "VideoWidgetTest.h"
#include "Frame.h"
#include <QApplication>

namespace view {
static TestResult test(int argc, char *argv[], QApplication *a) {
	TestResult r("view");

	/*VideoWidgetTest mainWindow = VideoWidgetTest();
	mainWindow.show();*/
	QImage testImage = QImage(":/cttUnitTests/BigBuckBunny.png");
	QOffscreenSurface surface;
	surface.create();
	QSharedPointer<QOpenGLContext> testContext = QSharedPointer<QOpenGLContext>(new QOpenGLContext());
	testContext->create();
	testContext->makeCurrent(&surface);
	testImage.load(":/cttUnitTests/BigBuckBunny.png");

	model::frame::Frame testFrame(testContext, testImage);

	VideoWidget testVideoWidget = VideoWidget(&testFrame);
	testVideoWidget.show();
	a->exec();

	return r;
}
} //namespace view

#endif 
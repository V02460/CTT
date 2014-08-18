#include "VideoWidgetTest.h"
#include "Frame.h"
#include "VideoWidget.h"

#include <QImage>
#include <QSharedPointer>
#include <QOpenGLContext>
#include <QWidget>
#include <QOffscreenSurface>

using model::frame::Frame;
using view::VideoWidget;

VideoWidgetTest::VideoWidgetTest() {
	resize(640, 480);

	QImage testImage = QImage(":/cttUnitTests/BigBuckBunny.png");
	QOffscreenSurface testSurface;
	testSurface.create();
	QSharedPointer<QOpenGLContext> testContext = QSharedPointer<QOpenGLContext>(new QOpenGLContext);
	testContext->create();
	testContext->makeCurrent(&testSurface);
	testImage.load(":/cttUnitTests/BigBuckBunny.png");
	Frame testFrame(testContext, testImage);

	VideoWidget testVideoWidget = VideoWidget(&testFrame);

	setCentralWidget(QWidget::createWindowContainer(&testVideoWidget, this));
}
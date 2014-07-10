#include "FrameTest.h"
#include "../ctt/Frame.h"
#include "CustomTestingMacros.h"
#include "../ctt/IllegalArgumentException.h"
#include "QOffscreenSurface"
#include "QDebug"

using namespace model::frame;
using namespace exception;

void FrameTest::withoutImageInvalid()
{
	QSize testSize(10, 0);
	FrameMetadata testMetadata(testSize);
	QEXPECT_EXCEPTION(Frame testframe(testContext, testMetadata), IllegalArgumentException);

	QSize testSize2(0, 10);
	FrameMetadata testMetadata2(testSize2);
	QEXPECT_EXCEPTION(Frame testframe(testContext, testMetadata2), IllegalArgumentException);	
}

void FrameTest::withImageInvalid()
{
	//TODO! bild hat Größe 0*0!
	QImage testImage("../Resources/big_buck_bunny_01337.png");

	QSize testSize(10, 0);
	FrameMetadata testMetadata(testSize);
	QEXPECT_EXCEPTION(Frame testframe(testContext, testImage, testMetadata), IllegalArgumentException);

	QSize testSize2(0, 10);
	FrameMetadata testMetadata2(testSize2);
	QEXPECT_EXCEPTION(Frame testframe(testContext, testImage, testMetadata2), IllegalArgumentException);
}

void FrameTest::initTestCase()
{
	surface.create();
	testContext = QSharedPointer<QOpenGLContext>(new QOpenGLContext());
	testContext->create();
	QVERIFY2(testContext->makeCurrent(&surface), "Couldn't initialize OGL Context.");
}

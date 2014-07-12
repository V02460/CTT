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
	QSize testSize(10, 0);
	FrameMetadata testMetadata(testSize);
	QEXPECT_EXCEPTION(Frame testframe(testContext, testImage, testMetadata), IllegalArgumentException);

	QSize testSize2(0, 10);
	FrameMetadata testMetadata2(testSize2);
	QEXPECT_EXCEPTION(Frame testframe(testContext, testImage, testMetadata2), IllegalArgumentException);

	QSize testSize3(10, 10);
	FrameMetadata testMetadata3(testSize3);
	QEXPECT_EXCEPTION(Frame testframe(testContext, testImage, testMetadata3), IllegalArgumentException);

	QImage testImage2(0, 0, QImage::Format_RGB888);
	QEXPECT_EXCEPTION(Frame testframe(testContext, testImage2, testMetadata3), IllegalArgumentException);
}

void FrameTest::initTestCase()
{
	surface.create();
	testContext = QSharedPointer<QOpenGLContext>(new QOpenGLContext());
	testContext->create();
	QVERIFY2(testContext->makeCurrent(&surface), "Couldn't initialize OGL Context.");

	testImage.load(":/cttUnitTests/BigBuckBunny.png");

	if (testImage.isNull()) {
		QFAIL("Unable to load image.");
	}
}

void FrameTest::withoutImage()
{
	QSize testSize(1920, 1080);
	FrameMetadata testMetadata(testSize);
	Frame testframe(testContext, testMetadata);

	QVERIFY2(testframe.shareGroup() == testContext->shareGroup(), "The created frame didn't save the OGL Context correctly.");

	//TODO write the testImage to the texture of the frame and check whether it worked, test metadata
}

void FrameTest::withImage()
{
	QSize testSize(1920, 1080);
	FrameMetadata testMetadata(testSize);
	Frame testframe(testContext, testImage, testMetadata);

	QVERIFY2(testframe.shareGroup() == testContext->shareGroup(), "The created frame didn't save the OGL Context correctly.");

	//TODO test the texture, write the to the texture of the frame and check whether it worked, test metadata
}

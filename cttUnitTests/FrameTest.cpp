#include "FrameTest.h"
#include "../ctt/Frame.h"
#include "CustomTestingMacros.h"
#include "../ctt/IllegalArgumentException.h"
#include "QOffscreenSurface"


using namespace model::frame;
using namespace exception;

void FrameTest::withoutImageInvalid()
{
	QSize testSize(10, 0);
	FrameMetadata testMetadata(testSize);
	
	QOffscreenSurface surface;
	surface.create();

	QSharedPointer<QOpenGLContext> testContext(new QOpenGLContext());
	testContext->create();

	QVERIFY2(testContext->makeCurrent(&surface), "Couldn't initialize OGL Context.");

	QEXPECT_EXCEPTION(Frame testframe(testContext, testMetadata), IllegalArgumentException);

	QSize testSize2(0, 10);
	FrameMetadata testMetadata2(testSize);
	QEXPECT_EXCEPTION(Frame testframe(testContext, testMetadata), IllegalArgumentException);	
}

void FrameTest::withImageInvalid()
{

}

#include "FrameTest.h"
#include "../ctt/Frame.h"
#include "CustomTestingMacros.h"
#include "../ctt/IllegalArgumentException.h"


using namespace model::frame;
using namespace exception;

void FrameTest::withoutImageInvalid()
{
	QSize testSize(10, 0);
	FrameMetadata testMetadata(testSize);
	QSharedPointer<QOpenGLContext> testContext(new QOpenGLContext());

	QEXPECT_EXCEPTION(Frame testframe(testContext, testMetadata), IllegalArgumentException);

	QSize testSize2(0, 10);
	FrameMetadata testMetadata2(testSize);
	QEXPECT_EXCEPTION(Frame testframe(testContext, testMetadata), IllegalArgumentException);
	
}

#include <CppUnitTest.h>
#include <functional>

#include "Frame.h"
#include "GlobalContext.h"

#include "IllegalArgumentException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ctt_unit_tests {

using model::frame::Frame;
using model::frame::FrameMetadata;
using model::GlobalContext;
using exception::IllegalArgumentException;

TEST_CLASS(FrameTest) {

public:
	TEST_METHOD(withoutImageInvalid) {
	QSize testSize(10, 0);
	FrameMetadata testMetadata(testSize);
	Assert::ExpectException<IllegalArgumentException>([&] {Frame testframe(testContext, testMetadata);});

	QSize testSize2(0, 10);
	FrameMetadata testMetadata2(testSize2);
	Assert::ExpectException<IllegalArgumentException>([&] {Frame testframe(testContext, testMetadata2);});	
}

	TEST_METHOD(withImageInvalid) {
	QImage testImage(":/cttUnitTests/BigBuckBunny.png");

	testImage.isNull();

	QSize testSize(10, 0);
	FrameMetadata testMetadata(testSize);
	Assert::ExpectException<IllegalArgumentException>([&] {Frame testframe(testContext, testImage, testMetadata);});

	QSize testSize2(0, 10);
	FrameMetadata testMetadata2(testSize2);
	Assert::ExpectException<IllegalArgumentException>([&] {Frame testframe(testContext, testImage, testMetadata2);});

	QSize testSize3(10, 10);
	FrameMetadata testMetadata3(testSize3);
	Assert::ExpectException<IllegalArgumentException>([&] {Frame testframe(testContext, testImage, testMetadata3);});

	QImage testImage2(0, 0, QImage::Format_RGB888);
	Assert::ExpectException<IllegalArgumentException>([&] {Frame testframe(testContext, testImage2, testMetadata3);});
}

TEST_METHOD_INITIALIZE(initTestCase)
{
    testContext = GlobalContext::get();
	
	testImage.load(":/cttUnitTests/BigBuckBunny.png");

	testImage.isNull();
}

TEST_METHOD(withoutImage) {
	QSize testSize(1920, 1080);
	FrameMetadata testMetadata(testSize);
	Frame testframe(testContext, testMetadata);

	testframe.shareGroup();
	testContext->shareGroup();
}

TEST_METHOD(withImage) {
	QSize testSize(1920, 1080);
	FrameMetadata testMetadata(testSize);
	Frame testframe(testContext, testImage, testMetadata);

	testframe.shareGroup();
	testContext->shareGroup();

}

private:
	QSharedPointer<QOpenGLContext> testContext;
	QImage testImage;

};
}
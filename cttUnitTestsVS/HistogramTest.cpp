#include <CppUnitTest.h>
#include <functional>

#include <QObject>
#include <QSharedPointer>
#include <QOpenGLContext>
#include <QImage>

#include "RedHistogram.h"
#include "GreenHistogram.h"
#include "BlueHistogram.h"
#include "HueHistogram.h"
#include "SaturationHistogram.h"
#include "LuminanceHistogram.h"
#include "Frame.h"
#include "GlobalContext.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using ::model::GlobalContext;
using ::exception::IllegalArgumentException;
using ::model::frame::Frame;
using ::model::frame::histogram::RedHistogram;
using ::model::frame::histogram::GreenHistogram;
using ::model::frame::histogram::BlueHistogram;
using ::model::frame::histogram::HueHistogram;
using ::model::frame::histogram::SaturationHistogram;
using ::model::frame::histogram::LuminanceHistogram;

namespace ctt_unit_tests {
	TEST_CLASS(HistogramTest) {
public:
	TEST_METHOD_INITIALIZE(initTestCase) {
		testContext = GlobalContext::get();

		testImage.load(":/cttUnitTests/BigBuckBunny.png");

		if (testImage.isNull()) {

		}

		Frame::sptr frame(new Frame(testContext, testImage));

		redHistogram = new RedHistogram(frame);
		greenHistogram = new GreenHistogram(frame);
		blueHistogram = new BlueHistogram(frame);
		hueHistogram = new HueHistogram(frame);
		saturationHistogram = new SaturationHistogram(frame);
		luminanceHistogram = new LuminanceHistogram(frame);
	}

	TEST_METHOD(histogramTypes) {
		redHistogram->getType();
		greenHistogram->getType();
		blueHistogram->getType();
		hueHistogram->getType();
		saturationHistogram->getType();
		luminanceHistogram->getType();
	}

	TEST_METHOD(getValues) {
		redHistogram->getValue(0);
		greenHistogram->getValue(128);
		Assert::ExpectException<IllegalArgumentException>([&]() {blueHistogram->getValue(512); });
		Assert::ExpectException<IllegalArgumentException>([&]() {hueHistogram->getValue(666); });
		Assert::ExpectException<IllegalArgumentException>([&]() {luminanceHistogram->getValue(256); });
		saturationHistogram->getValue(255);
	}

private:
	QSharedPointer<QOpenGLContext> testContext;
	QImage testImage;

	RedHistogram *redHistogram;
	GreenHistogram *greenHistogram;
	BlueHistogram *blueHistogram;
	HueHistogram *hueHistogram;
	SaturationHistogram *saturationHistogram;
	LuminanceHistogram *luminanceHistogram;
	};
}
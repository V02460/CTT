#include <CppUnitTest.h>
#include <functional>

#include <QObject>
#include "YUVDataVideo.h"
#include "MixFilter.h"
#include "FilterParam.h"
#include "GlobalContext.h"
#include "AccessToDummyException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using model::filter::MixFilter;
using model::video::YUVDataVideo;
using model::filter::FilterParam;
using model::GlobalContext;
using model::video::YUVType;
using model::saveable::Memento;
using exception::AccessToDummyException;

namespace ctt_unit_tests {
	TEST_CLASS(MixFilterTest) {
public:
	TEST_METHOD_INITIALIZE(initTestCase) {
		testContext = GlobalContext::get();

		video1.reset(new YUVDataVideo("Resources/Videos/YUV422/squirrel-720x576-422P.yuv",
			QSize(720, 576),
			24,
			YUVType::YUV422,
			testContext));

		video2.reset(new YUVDataVideo("Resources/Videos/YUV444/squirrel-720x576-444P.yuv",
			QSize(720, 576),
			24,
			YUVType::YUV444,
			testContext));
	}

	TEST_METHOD(testRun) {
		MixFilter mixFilter(video1, video2);
		mixFilter.getFrame(13);
	}

	TEST_METHOD(wrongParams) {
		MixFilter mixFilter(video1, video2);
		Assert::ExpectException<IllegalArgumentException>([&]() {mixFilter.setParam(FilterParam::sptr(new FilterParam("not right", "at all")));});
		Assert::ExpectException<IllegalArgumentException>([&]() {mixFilter.setParam(FilterParam::sptr(new FilterParam("a bit off", 1.0)));});
		Assert::ExpectException<IllegalArgumentException>([&]() {mixFilter.setParam(FilterParam::sptr(new FilterParam(MixFilter::kParamMixRatioStr, "WRONG!")));});
		mixFilter.getFrame(9);
		mixFilter.setParam(FilterParam::sptr(new FilterParam(MixFilter::kParamMixRatioStr, 10.0f)));
		mixFilter.getFrame(14);
		mixFilter.setParam(FilterParam::sptr(new FilterParam(MixFilter::kParamMixRatioStr, -3.5f)));
		mixFilter.getFrame(3);
	}

	TEST_METHOD(differentSize) {
		YUVDataVideo::sptr video3(
			new YUVDataVideo("Resources/Videos/YUV420/waterfall_cif_420_352x288_260frames.yuv",
			QSize(352, 288),
			24,
			YUVType::YUV420,
			testContext));

		//TODO: macro not working
		//QFAIL("Exception testing macro not working properly, so i put this here...");
		Assert::ExpectException<IllegalArgumentException>([&]() {MixFilter(video1, video3); });
	}

	TEST_METHOD(memento) {
		MixFilter testFilter(video1, video2);
		testFilter.setParam(FilterParam::sptr(new FilterParam(MixFilter::kParamMixRatioStr, 0.314f)));

		Memento memento = testFilter.getMemento();

		MixFilter::sptr dummyFilter = MixFilter::getDummy().dynamicCast<MixFilter>();
		Assert::ExpectException<AccessToDummyException>([&]() {dummyFilter->getFrame(7); });
		Assert::ExpectException<AccessToDummyException>([&]() {dummyFilter->getMemento(); });
		Assert::ExpectException<AccessToDummyException>([&]() {dummyFilter->getUsesList(); });
		
		Assert::IsTrue(dummyFilter->isDummy());

		dummyFilter->restore(memento);

		dummyFilter->getParamValue<float>(MixFilter::kParamMixRatioStr);

		dummyFilter->getFrame(6);
	}
private:
	QSharedPointer<QOpenGLContext> testContext;
	::model::video::YUVDataVideo::sptr video1;
	::model::video::YUVDataVideo::sptr video2;
	};
}
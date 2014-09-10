#include <CppUnitTest.h>
#include <functional>

#include "YUVDataVideo.h"
#include "FilteredVideo.h"
#include "GreyscaleFilter.h"
#include "Memento.h"
#include "GlobalContext.h"

#include "IllegalStateException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ctt_unit_tests {

using model::video::YUVDataVideo;
using model::filter::FilteredVideo;
using model::filter::GreyscaleFilter;
using model::GlobalContext;
using exception::IllegalArgumentException;
using model::saveable::Memento;

TEST_CLASS(FilteredVideoTest) {
public:
TEST_METHOD_INITIALIZE(initTestCase)
{
    testContext = GlobalContext::get();
}

TEST_METHOD(dummyTest) {
	model::saveable::Saveable::sptr dummy = FilteredVideo::getDummy();
	dummy->isDummy();
}

TEST_METHOD(filterOperations) {
	model::video::YUVDataVideo::sptr baseVideo(
        new model::video::YUVDataVideo("Resources/Videos/YUV444/squirrel-720x576-444P.yuv",
                                       QSize(720, 576),
                                       24,
                                       model::video::YUVType::YUV444,
                                       testContext));

	FilteredVideo testVideo(baseVideo);

	testVideo.getContext() == baseVideo->getContext();
	testVideo.getFilterCount();
	testVideo.getFilterList().isEmpty();
	testVideo.getBaseVideo() == baseVideo;
	testVideo.getUsesList().contains(baseVideo.data());
	testVideo.getUsesList().contains(&testVideo);
	testVideo.uses(*baseVideo.data());
	testVideo.uses(testVideo);
	testVideo.getUsesList().size();
	testVideo.getFrameCount();

	model::video::YUVDataVideo::sptr predecessorVideo(new model::video::YUVDataVideo("resources/Videos/YUV444/squirrel-720x576-444P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV444, testContext));


	GreyscaleFilter::sptr filter0(new GreyscaleFilter(predecessorVideo));

	Assert::ExpectException<IllegalArgumentException>([&] {testVideo.addFilter(filter0, 4);});

	testVideo.addFilter(filter0, 0);
	testVideo.getFilterCount();
	testVideo.getFilterList().at(0) == filter0;

	GreyscaleFilter::sptr filter1(new GreyscaleFilter(predecessorVideo));
	testVideo.addFilter(filter1, 0);
	testVideo.getFilterCount();
	testVideo.getFilterList().at(0) == filter1;
	testVideo.getFilterList().at(1) == filter0;

	GreyscaleFilter::sptr filter2(new GreyscaleFilter(predecessorVideo));
	testVideo.addFilter(filter2, 2);
	testVideo.getFilterCount();
	testVideo.getFilterList().at(0) == filter1;
	testVideo.getFilterList().at(1) == filter0;
	testVideo.getFilterList().at(2) == filter2;

	GreyscaleFilter::sptr filter3(new GreyscaleFilter(predecessorVideo));
	testVideo.addFilter(filter3, 2);
	testVideo.getFilterCount();
	testVideo.getFilterList().at(0) == filter1;
	testVideo.getFilterList().at(1) == filter0;
	testVideo.getFilterList().at(2) == filter3;
	testVideo.getFilterList().at(3) == filter2;

	//TODO adjust this when decision for correct implementation is made
	testVideo.getUsesList().size();

	testVideo.uses(*filter0);
	testVideo.uses(*filter1);
	testVideo.uses(*filter2);
	testVideo.uses(*filter3);

	testVideo.removeFilter(2);
	testVideo.getFilterCount();
	testVideo.getFilterList().at(0) == filter1;
	testVideo.getFilterList().at(1) == filter0;
	testVideo.getFilterList().at(2) == filter2;

	testVideo.removeFilter(2);
	testVideo.getFilterCount();
	testVideo.getFilterList().at(0) == filter1;
	testVideo.getFilterList().at(1) == filter0;

	testVideo.removeFilter(0);
	testVideo.getFilterCount();
	testVideo.getFilterList().at(0) == filter0;

	testVideo.removeFilter(0);
	testVideo.getFilterCount();

}

TEST_METHOD(saveRestore) {
	model::video::YUVDataVideo::sptr baseVideo(
		new model::video::YUVDataVideo("Resources/Videos/YUV444/squirrel-720x576-444P.yuv",
		QSize(720, 576),
		24,
		model::video::YUVType::YUV444,
		testContext));

	FilteredVideo::sptr testVideoPointer(new FilteredVideo(baseVideo));

	GreyscaleFilter::sptr filter0(new GreyscaleFilter(testVideoPointer));
	testVideoPointer->addFilter(filter0, 0);

	GreyscaleFilter::sptr filter1(new GreyscaleFilter(testVideoPointer));
	testVideoPointer->addFilter(filter1, 0);

	GreyscaleFilter::sptr filter2(new GreyscaleFilter(testVideoPointer));
	testVideoPointer->addFilter(filter2, 2);

	GreyscaleFilter::sptr filter3(new GreyscaleFilter(testVideoPointer));
	testVideoPointer->addFilter(filter3, 2);

	Memento memento = testVideoPointer->getMemento();

	FilteredVideo::sptr dummy = FilteredVideo::getDummy().dynamicCast<FilteredVideo>();
	dummy->restore(memento);
	dummy->getContext() == baseVideo->getContext();
	dummy->getBaseVideo() == baseVideo;
	dummy->getFilterCount();
	dummy->getFilterList().at(0) == filter1;
	dummy->getFilterList().at(1) == filter0;
	dummy->getFilterList().at(2) == filter3;
	dummy->getFilterList().at(3) == filter2;

	testVideoPointer->removeFilter(1);
	testVideoPointer->restore(memento);
	testVideoPointer->getContext() == baseVideo->getContext();
	testVideoPointer->getBaseVideo() == baseVideo;
	testVideoPointer->getFilterCount();
	testVideoPointer->getFilterList().at(0) == filter1;
	testVideoPointer->getFilterList().at(1) == filter0;
	testVideoPointer->getFilterList().at(2) == filter3;
	testVideoPointer->getFilterList().at(3) == filter2;
}
private:
	QSharedPointer<QOpenGLContext> testContext;

};
}
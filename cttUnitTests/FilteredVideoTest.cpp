#include "FilteredVideoTest.h"

#include "CustomTestingMacros.h"
#include "YUVDataVideo.h"
#include "FilteredVideo.h"
#include "GreyscaleFilter.h"
#include "Memento.h"
#include "GlobalContext.h"

#include "IllegalStateException.h"

using model::video::YUVDataVideo;
using model::filter::FilteredVideo;
using model::filter::GreyscaleFilter;
using model::GlobalContext;
using exception::IllegalArgumentException;

void FilteredVideoTest::initTestCase()
{
    testContext = GlobalContext::get();
}

void FilteredVideoTest::dummyTest()
{
	model::saveable::Saveable::sptr dummy = FilteredVideo::getDummy();
	QVERIFY(dummy->isDummy());
}

void FilteredVideoTest::filterOperations()
{
	model::video::YUVDataVideo::sptr baseVideo(
        new model::video::YUVDataVideo("Resources/Videos/YUV444/squirrel-720x576-444P.yuv",
                                       QSize(720, 576),
                                       24,
                                       model::video::YUVType::YUV444,
                                       testContext));

	FilteredVideo testVideo(baseVideo);

	QVERIFY(testVideo.getContext() == baseVideo->getContext());
	QCOMPARE(testVideo.getFilterCount(), 0U);
	QVERIFY(testVideo.getFilterList().isEmpty());
	QVERIFY(testVideo.getBaseVideo() == baseVideo);
	QVERIFY(testVideo.getUsesList().contains(baseVideo.data()));
	QVERIFY(testVideo.getUsesList().contains(&testVideo));
	QVERIFY(testVideo.uses(*baseVideo.data()));
	QVERIFY(testVideo.uses(testVideo));
	QCOMPARE(testVideo.getUsesList().size(), 2);
	QCOMPARE(testVideo.getFrameCount(), baseVideo->getFrameCount());

	model::video::YUVDataVideo::sptr predecessorVideo(new model::video::YUVDataVideo("resources/Videos/YUV444/squirrel-720x576-444P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV444, testContext));


	GreyscaleFilter::sptr filter0(new GreyscaleFilter(predecessorVideo));

	QEXPECT_EXCEPTION(testVideo.addFilter(filter0, 4), IllegalArgumentException);

	testVideo.addFilter(filter0, 0);
	QCOMPARE(testVideo.getFilterCount(), 1U);
	QVERIFY(testVideo.getFilterList().at(0) == filter0);

	GreyscaleFilter::sptr filter1(new GreyscaleFilter(predecessorVideo));
	testVideo.addFilter(filter1, 0);
	QCOMPARE(testVideo.getFilterCount(), 2U);
	QVERIFY(testVideo.getFilterList().at(0) == filter1);
	QVERIFY(testVideo.getFilterList().at(1) == filter0);

	GreyscaleFilter::sptr filter2(new GreyscaleFilter(predecessorVideo));
	testVideo.addFilter(filter2, 2);
	QCOMPARE(testVideo.getFilterCount(), 3U);
	QVERIFY(testVideo.getFilterList().at(0) == filter1);
	QVERIFY(testVideo.getFilterList().at(1) == filter0);
	QVERIFY(testVideo.getFilterList().at(2) == filter2);

	GreyscaleFilter::sptr filter3(new GreyscaleFilter(predecessorVideo));
	testVideo.addFilter(filter3, 2);
	QCOMPARE(testVideo.getFilterCount(), 4U);
	QVERIFY(testVideo.getFilterList().at(0) == filter1);
	QVERIFY(testVideo.getFilterList().at(1) == filter0);
	QVERIFY(testVideo.getFilterList().at(2) == filter3);
	QVERIFY(testVideo.getFilterList().at(3) == filter2);

	//TODO adjust this when decision for correct implementation is made
	QCOMPARE(testVideo.getUsesList().size(), 6);

	QVERIFY(testVideo.uses(*filter0));
	QVERIFY(testVideo.uses(*filter1));
	QVERIFY(testVideo.uses(*filter2));
	QVERIFY(testVideo.uses(*filter3));

	testVideo.removeFilter(2);
	QCOMPARE(testVideo.getFilterCount(), 3U);
	QVERIFY(testVideo.getFilterList().at(0) == filter1);
	QVERIFY(testVideo.getFilterList().at(1) == filter0);
	QVERIFY(testVideo.getFilterList().at(2) == filter2);

	testVideo.removeFilter(2);
	QCOMPARE(testVideo.getFilterCount(), 2U);
	QVERIFY(testVideo.getFilterList().at(0) == filter1);
	QVERIFY(testVideo.getFilterList().at(1) == filter0);

	testVideo.removeFilter(0);
	QCOMPARE(testVideo.getFilterCount(), 1U);
	QVERIFY(testVideo.getFilterList().at(0) == filter0);

	testVideo.removeFilter(0);
	QCOMPARE(testVideo.getFilterCount(), 0U);

}

void FilteredVideoTest::saveRestore()
{
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
	QVERIFY(dummy->getContext() == baseVideo->getContext());
	QVERIFY(dummy->getBaseVideo() == baseVideo);
	QCOMPARE(dummy->getFilterCount(), 4U);
	QVERIFY(dummy->getFilterList().at(0) == filter1);
	QVERIFY(dummy->getFilterList().at(1) == filter0);
	QVERIFY(dummy->getFilterList().at(2) == filter3);
	QVERIFY(dummy->getFilterList().at(3) == filter2);

	testVideoPointer->removeFilter(1);
	testVideoPointer->restore(memento);
	QVERIFY(testVideoPointer->getContext() == baseVideo->getContext());
	QVERIFY(testVideoPointer->getBaseVideo() == baseVideo);
	QCOMPARE(testVideoPointer->getFilterCount(), 4U);
	QVERIFY(testVideoPointer->getFilterList().at(0) == filter1);
	QVERIFY(testVideoPointer->getFilterList().at(1) == filter0);
	QVERIFY(testVideoPointer->getFilterList().at(2) == filter3);
	QVERIFY(testVideoPointer->getFilterList().at(3) == filter2);
}
